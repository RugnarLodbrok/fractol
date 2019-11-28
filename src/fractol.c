#include "fractol.h"

void t_fractol_init(t_fractol *f, int w, int h)
{
	f->w = w;
	f->h = h;
	f->data = ft_memalloc(sizeof(t_fractol_pix) * w * h);
}

void t_fractol_iteration(t_fractol *f, int tc, int ti)
{
	int n;
	int i;
	int k;
	t_fractol_pix *p;

	n = f->w * f->h;
	i = -tc + ti;
	while ((i += tc) < n)
	{
		p = &f->data[i];
		if (p->stop)
			continue;
		k = 10;
		while(k--)
		{
			if (t_fractol_pix_iteration(p) == INT_MAX)
			{
//				f->it_distribution[p->i]++;
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
	int draw_black;

	n = f->w * f->h;
	i = -1;
	draw_black = 1;//check_for_draw_black(f);
	while (++i < n)
	{
		p = &f->data[i];
		if (p->stop)
		{
			if (p->i != -1) //i == -1 means no need to recalculate color;
			{
				p->color = hue_spiral(p->i);
				p->i = -1;
			}
			fb->data[i] = p->color;
		}
		else if (draw_black)
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
	while (++i < w)
	{
		j = -1;
		while (++j < f->h)
		{
			p = t_vec_transform((t_vec){i, j, 0}, m);
			pix = &f->data[j * w + i];
			pix->c = (t_complex){p.x, p.y};
			pix->z = (t_complex){0, p.z};
			pix->i = 0;
			pix->stop = 0;
			pix->color = 0;
		}
	}
}
