#include "fractol.h"
#include <math.h>

/*
** todo: have a special renderer thread that renders in 1/4 resolution to smoothen movement
*/

void t_fractol_init(t_fractol *f, int w, int h)
{
	int i;

	f->w = w;
	f->h = h;
	f->data = ft_memalloc(sizeof(t_fractol_pix) * w * h);
	f->color_cache = malloc(sizeof(uint) * MAX_ITER);
	i = -1;
	while (++i < MAX_ITER)
		f->color_cache[i] = hue_spiral(i);
	t_ies_init(&f->ies);
}

void t_fractol_iteration(t_fractol *f, int tc, int ti)
{
	int n;
	int i;
	uint k;
	t_fractol_pix *p;

	n = f->w * f->h;
	i = -tc + ti;
	while ((i += tc) < n)
	{
		p = &f->data[i];
		if (p->stop)
			continue;
		k = (p->i << 2) + 1;
		if (k > 0x20)
			k = 0x20;
		while (k--)
		{
			if (t_fractol_pix_iteration(p) == INT_MAX)
			{
				t_ies_add(&f->ies, p->i);
				break;
			}
		}
	}
}

void t_fractol_draw(t_fractol *f, t_framebuffer *fb)
{
	int n;
	int i;
	t_fractol_pix *p;
	int it_estimation;

	n = f->w * f->h;
	i = -1;
	it_estimation = t_ies_estimate(&f->ies);
	while (++i < n)
	{
		p = &f->data[i];
		if (p->stop)
			fb->data[i] = f->color_cache[p->i];
		else if (p->i > it_estimation)
			fb->data[i] = 0;
	}
}

static void rotate_m_to_j(t_vec *z, t_vec *c, double a)
{
	t_vec tmp;
	double si;
	double co;

	si = sin(a);
	co = cos(a);
	tmp = (t_vec){z->x, c->x};
	z->x = tmp.x * co + tmp.y * si;
	c->x = -tmp.x * si + tmp.y * co;
	tmp = (t_vec){z->y, c->y};
	z->y = tmp.x * co + tmp.y * si;
	c->y = -tmp.x * si + tmp.y * co;
}

void t_fractol_reset(t_fractol *f, t_cam *cam)
{
	int i;
	int j;
	int w;
	t_mat m;
	t_vec z;
	t_vec c;
	double angle;

	m = t_mat_mul_ref(&cam->m, &cam->d);
	w = f->w;
	i = -1;
	t_ies_reset(&f->ies);
	angle = (double)cam->rot_angle / 100;
	ft_printf("angle: %f\n", angle);
	while (++i < w)
	{
		j = -1;
		while (++j < f->h)
		{
			c = t_vec_transform((t_vec){i, j}, m);
			z = (t_vec){0, .6357 * sin(angle), 0};
			rotate_m_to_j(&z, &c, angle);
			t_fractol_pix_reset(&f->data[j * w + i],
								*(t_complex *)&z,
								*(t_complex *)&c);
		}
	}
}
