#include <limits.h>
#include "fractol.h"

void t_fractol_pix_reset(t_fractol_pix *pix, t_vec *p)
{
	pix->c = (t_complex){p->x, p->y};
	pix->z = (t_complex){p->z, 0};
	pix->i = 0;
	pix->stop = 0;
	pix->color = 0;
}

int t_fractol_pix_iteration(t_fractol_pix *p, uint *color_cache)
{
	t_complex z;
	t_complex c;

	if (p->stop)
		return (INT_MAX);
	z = p->z;
	if (z.re * z.re + z.im * z.im > 4 || p->i >= MAX_ITER - 1)
	{
		p->color = color_cache[p->i];
		p->stop = 1;
		return (INT_MAX);
	}
	c = p->c;
	p->z = (t_complex){z.re * z.re - z.im * z.im + c.re,
					   z.re * z.im * 2 + c.im};
	p->i++;
	return (p->i);
}
