#include "libft.h"
#include "fractol.h"
#include "mlx.h"
#include <time.h>

uint iteration_color(int iteration)
{
	return (iteration % 25) * 10 * RED;
}

uint mandelbrot_pixel(double x, double y)
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
			return iteration_color(i);
	}
	return (0);
}

void draw_fractol(t_framebuffer *f)
{
	int i;
	int j;
	double x;
	double y;

	i = -1;
	while (++i < f->w)
	{
		j = -1;
		while (++j < f->h)
		{
			x = (double)(i - 2 * f->w / 3) / 200;
			y = (double)(j - f->h / 2) / 200;
			fb_put_pixel(f, i, j, mandelbrot_pixel(x, y));
		}
	}
}

void update(t_app *app, double dt)
{
	t_framebuffer_clear(&app->framebuffer);
	draw_fractol(&app->framebuffer);
	mlx_put_image_to_window(app->M, app->win, app->framebuffer.image, 0, 0);
}

int loop_hook(t_app *app)
{
	double dt;

	app->time = clock();
	dt = (double)(app->time - app->frame_time) / CLOCKS_PER_SEC;
	if (dt > FRAME_TIME)
	{
		app->frame_time = app->time;
		update(app, dt);
	}
	return (0);
}

int close_hook(void *param)
{
	(void)param;
	exit(0);
}

int main()
{
	t_app app;

	t_app_init(&app);
//	print_info(&app);
	mlx_loop_hook(app.M, loop_hook, &app);
	mlx_hook(app.win, MLX_EVENT_EXIT, 0, &close_hook, 0);
	mlx_loop(app.M);
	return (0);
}
