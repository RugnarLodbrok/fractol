#include "libft.h"
#include "fractol.h"
#include "threading.h"
#include "mlx.h"
#include "limits.h"

void update(t_app *app, double dt)
{
	t_cam_move(&app->cam, &app->controller, dt);
	t_fractol_draw(&app->fractol, &app->framebuffer);
	mlx_put_image_to_window(app->M, app->win, app->framebuffer.image,
							app->sidebar_w, 0);
}

static int mat_eq(t_mat *m1, t_mat *m2)
{
	if (m1->data[0][0] != m2->data[0][0])
		return 0;
	if (m1->data[1][1] != m2->data[1][1])
		return 0;
	if (m1->data[0][3] != m2->data[0][3])
		return 0;
	if (m1->data[1][3] != m2->data[1][3])
		return 0;
	if (m1->data[2][3] != m2->data[2][3])
		return 0;
	return (1);
}

void fractol_renderer(t_app *app, int tpool_c, int tpool_i)
{
	t_mat m;
	t_mat m_new;

	t_mat_reset(&m);
	t_mat_reset(&m_new);
	while (!app->shutdown)
	{
		m_new = t_mat_mul_ref(&app->cam.m, &app->cam.d);
		if (!mat_eq(&m_new, &m) && !tpool_i)
			t_fractol_reset(&app->fractol, m_new);
		m = m_new;
		t_fractol_iteration(&app->fractol, tpool_c, tpool_i);
	}
}

int fractol_v2()
{
	t_app app;
	t_tpool renderer;

	t_app_init(&app, update);
	t_fractol_init(&app.fractol, app.w, app.h);
	renderer = t_tpool_create(7, fractol_renderer, &app);
	t_app_up(&app);
	t_poool_start(&renderer);
	t_app_run(&app);
	return (0);
}
