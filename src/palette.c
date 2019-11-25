#include <math.h>
#include "libft.h"
#include "fractol.h"

uint color_3f(double r, double g, double b)
{
	return (
			RED * (int)(255 * r + .5) +
			GREEN * (int)(255 * g + .5) +
			BLUE * (int)(255 * b + .5));
}

uint hue_spiral(int iteration)
{
	double S = 1.;
	double L = (1 - exp(-(double)iteration / 10))/2;
	double H = (double)(iteration % 19) * 6 / 19;
	double C = (1 - fabs(2 * L - 1)) * S;
	double X = C * (1 - fabs(fmod(H, 2) - 1));
	if (H <= 1)
		return color_3f(C, X, 0);
	if (H <= 2)
		return color_3f(X, C, 0);
	if (H <= 3)
		return color_3f(0, C, X);
	if (H <= 4)
		return color_3f(0, X, C);
	if (H <= 5)
		return color_3f(X, 0, C);
	return color_3f(C, 0, X);
}
