#include <limits.h>
#include <math.h>
#include "fractol.h"

void t_fractol_pix_reset_julia(t_fractol_pix *pix, t_complex z, t_complex c)
{
	pix->c = z;
	pix->z = c;
	pix->i = 0;
	pix->stop = 0;
}

void t_fractol_pix_reset_mand(t_fractol_pix *pix, t_complex z, t_complex c)
{
	pix->c = c;
	pix->z = z;
	pix->i = 0;
	pix->stop = 0;
}

int t_fractol_pix_sin(t_fractol_pix *p)
{
	t_complex z;
	t_complex c;

	if (p->stop)
		return (INT_MAX);
	z = p->z;
	if (z.im * z.im > 100 || p->i >= MAX_ITER - 1)
	{
		p->stop = 1;
		return (INT_MAX);
	}
	c = p->c;
	p->z = (t_complex){sin(z.re)*cosh(z.im) + c.re,
					   cos(z.re)*sinh(z.im) + c.im};
	return (++p->i);
}

int t_fractol_pix_z2(t_fractol_pix *p)
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
