#include "libft.h"
#include "fractol.h"

uint mandelbrot_pixel(double x, double y)
{
	int iterations;
	t_complex z;
	int i;

	iterations = 30;
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

void draw_fractol(t_framebuffer *f, t_mat m)
{
	int i;
	int j;
	t_vec p;

	i = -1;
	while (++i < f->w)
	{
		j = -1;
		while (++j < f->h)
		{
			p = t_vec_transform((t_vec){i, j, 0}, m);
			fb_put_pixel(f, i, j, mandelbrot_pixel(p.x, p.y));
		}
	}
}

void update(t_app *app, double dt)
{
	t_view_move(&app->view, &app->controller);
	draw_fractol(&app->framebuffer, t_mat_mul_ref(&app->view.mi, &app->view.di));
}

int fractol()
{
	t_app app;

	t_app_init(&app, update);
	t_app_run(&app);
	return (0);
}

int main()
{
	fractol();
}
