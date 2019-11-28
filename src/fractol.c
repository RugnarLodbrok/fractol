#include "fractol.h"

/*
** todo: have a pecial renderer thread that renders in 1/4 resolution to smoothen movement
*/

void t_fractol_init(t_fractol *f, int w, int h)
{
	int i;

	f->w = w;
	f->h = h;
	f->data = ft_memalloc(sizeof(t_fractol_pix) * w * h);
	f->color_cache = malloc(sizeof(uint) * MAX_ITER);
	i = -1;
	while(++i < MAX_ITER)
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
		while(k--)
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

void t_fractol_reset(t_fractol *f, t_mat m)
{
	int i;
	int j;
	int w;
	t_fractol_pix *pix;
	t_vec p;

	w = f->w;
	i = -1;
	t_ies_reset(&f->ies);
	while (++i < w)
	{
		j = -1;
		while (++j < f->h)
		{
			p = t_vec_transform((t_vec){i, j, 0}, m);
			pix = &f->data[j * w + i];
			t_fractol_pix_reset(pix, &p);
		}
	}
}
