#include "libft.h"
#include "fractol.h"
#include "threading.h"
#include "mlx.h"

static uint mandelbrot_pixel(double x, double y)
{
	int iterations;
	t_complex z;
	int i;

	iterations = 100;
	z = (t_complex){0, 0};
	i = -1;
	while (++i < iterations)
	{
		z = (t_complex){z.re * z.re - z.im * z.im + x, z.re * z.im * 2 + y};
		if (z.re * z.re + z.im * z.im > 4)
			return hue_spiral(i);
	}
	return (0);
}

static void draw_fractol(t_framebuffer *f, t_mat m, int tpool_c, int tpool_i)
{
	int i;
	int j;
	t_vec p;

	i = -1;
	while (++i < f->w)
	{
		j = (tpool_i + 13 * i) % tpool_c;
		while (j < f->h)
		{
			p = t_vec_transform((t_vec){i, j, 0}, m);
			fb_put_pixel(f, i, j, mandelbrot_pixel(p.x, p.y));
			j += tpool_c;
		}
	}
}

static void update(t_app *app, double dt)
{
	t_view_move(&app->view, &app->controller, dt);
	mlx_put_image_to_window(app->M, app->win, app->framebuffer.image, app->sidebar_w, 0);
}

static void fractol_renderer(t_app *app, int tpool_c, int tpool_i)
{
	t_mat m;

	while(!app->shutdown)
	{
		m = t_mat_mul_ref(&app->view.m, &app->view.d);
		draw_fractol(&app->framebuffer, m, tpool_c, tpool_i);
	}
}

int fractol_v1()
{
	t_app app;
	t_tpool renderer;

	t_app_init(&app, update);
	renderer = t_tpool_create(6, fractol_renderer, &app);
	t_poool_start(&renderer);
	t_app_run(&app);
	return (0);
}
