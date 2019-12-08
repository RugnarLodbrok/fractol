#include "fractol.h"
#include "threading.h"
#include "mlx.h"

void update(t_app *app, double dt)
{
	t_cam_move(&app->cam, &app->controller, dt);
	t_fractol_draw(&app->fractol, &app->framebuffer);
	mlx_put_image_to_window(app->M, app->win, app->framebuffer.image,
							app->sidebar_w, 0);
}

static void fractol_renderer(void *p, t_thread_id ti)
{
	uint	mask;
	uint	mask_inverted;
	t_app	*app;

	app = p;
	mask = 1 << ti.i;
	mask_inverted = mask ^ 0xFFFFFFFF;
	while (!app->shutdown)
	{
		if (app->cam.is_changed & mask)
		{
			app->cam.is_changed &= mask_inverted;
			t_fractol_reset(&app->fractol, &app->cam, ti);
		}
		t_fractol_iteration(&app->fractol, ti);
	}
}

int fractol_main(int fractal_type)
{
	t_app app;
	t_tpool renderer;

	t_app_init(&app, update);
	t_fractol_init(&app.fractol, app.w, app.h, fractal_type);
	if (fractal_type == FRACTOL_MAND_Z2)
		app.cam.julia_offset.y = -10;
	renderer = t_tpool_create(7, fractol_renderer, &app);
	t_app_up(&app);
	t_pool_start(&renderer);
	t_app_run(&app);
	return (0);
}
