#include <limits.h>
#include "fractol.h"

int t_fractol_pix_iteration(t_fractol_pix *p)
{
	t_complex z;
	t_complex c;

	if (p->stop)
		return (INT_MAX);
	z = p->z;
	if (z.re * z.re + z.im * z.im > 4)
	{
		p->stop = 1;
		return (INT_MAX);
	}
	c = p->c;
	p->z = (t_complex){z.re * z.re - z.im * z.im + c.re,
					   z.re * z.im * 2 + c.im};
	p->i++;
	return (p->i);
}
