#include "libft.h"
#include "fractol.h"
#include "threading.h"
#include "mlx.h"

static void t_fractol_iteration(t_fractol *f, int tc, int ti)
{
	int n;
	int i;
	t_complex z;
	t_complex c;
	t_fractol_pix *p;

	n = f->w * f->h;
	i = -tc + ti;
	while ((i += tc) < n)
	{
		p = &f->data[i];
		if (p->stop)
			continue;
		z = p->z;
		if (z.re * z.re + z.im * z.im > 4)
		{
			p->stop = 1;
			continue;
		}
		c = p->c;
		p->z = (t_complex){z.re * z.re - z.im * z.im + c.re,
						   z.re * z.im * 2 + c.im};
		p->i++;
	}
}

void t_fractol_draw(t_fractol *f, t_framebuffer *fb)
{
	int n;
	int i;
	t_fractol_pix *p;

	n = f->w * f->h;
	i = -1;
	while (++i < n)
	{
		p = &f->data[i];
		if (p->stop && p->i != -1)
		{
			p->color = hue_spiral(p->i);
			if (p->stop)
				p->i = -1;
		}
		fb->data[i] = p->color;
	}
}

void update(t_app *app, double dt)
{
	t_view_move(&app->view, &app->controller, dt);
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
	return (1);
}

void t_fractol_reset(t_fractol *f, t_mat m)
{
	int i;
	int j;
	int w;
	t_fractol_pix *pix;
	t_vec p;

	w = f->w;
	i = -1;
	while (++i < w)
	{
		j = -1;
		while (++j < f->h)
		{
			p = t_vec_transform((t_vec){i, j, 0}, m);
			pix = &f->data[j * w + i];
			pix->c = (t_complex){p.x, p.y};
			pix->z = (t_complex){0, 0};
			pix->i = 0;
			pix->stop = 0;
			pix->color = 0;
		}
	}
}

void fractol_renderer(t_app *app, int tpool_c, int tpool_i)
{
	t_mat m;
	t_mat m_new;

	t_mat_reset(&m);
	t_mat_reset(&m_new);
	while (!app->shutdown)
	{
		m_new = t_mat_mul_ref(&app->view.mi, &app->view.di);
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
	app.fractol.w = app.framebuffer.w;
	app.fractol.h = app.framebuffer.h;
	app.fractol.data = ft_memalloc(sizeof(t_fractol_pix) * app.w * app.h);
	renderer = t_tpool_create(6, fractol_renderer, &app);
	t_poool_start(&renderer);
	t_app_run(&app);
	return (0);
}
