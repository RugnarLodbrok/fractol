#include <limits.h>
#include "fractol.h"

void t_fractol_pix_reset(t_fractol_pix *pix, t_complex z, t_complex c)
{
	pix->c = c;
	pix->z = c;
	pix->i = 0;
	pix->stop = 0;
}

int t_fractol_pix_iteration(t_fractol_pix *p)
{
	t_complex z;
	t_complex c;

	if (p->stop)
		return (INT_MAX);
	z = p->z;
	if (z.re * z.re + z.im * z.im > 4 || p->i >= MAX_ITER - 1)
	{
		p->stop = 1;
		return (INT_MAX);
	}
	c = p->c;
	p->z = (t_complex){z.re * z.re - z.im * z.im + c.re,
					   z.re * z.im * 2 + c.im};
	return (++p->i);
}
