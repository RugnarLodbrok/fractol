#include "libft.h"
#include "fractol.h"

void fractol_v1();
void fractol_main(int fractal_type);

int parse_av(int ac, char **av)
{
	char *type;

	if (ac != 2)
		ft_error_exit(HELP);
	type = av[1];
	if (!ft_strcmp(type, "mandelbrot"))
		return FRACTOL_MAND_Z2;
	if (!ft_strcmp(type, "mandelbrot_sin"))
		return FRACTOL_MAND_SIN;
	if (!ft_strcmp(type, "julia"))
		return FRACTOL_JULIA_Z2;
	if (!ft_strcmp(type, "julia_sin"))
		return FRACTOL_JULIA_SIN;
	ft_error_exit(HELP);
	return (0);
}

int main(int ac, char **av)
{
	int fractal_type;

	fractal_type = parse_av(ac, av);
	fractol_main(fractal_type);
}
