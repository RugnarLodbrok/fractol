#include <math.h>
#include "fractol.h"

void t_cam_init(t_cam *cam, int w, int h)
{
	double scale_factor;

	t_mat_reset(&cam->m);
	cam->zoom = 0;
	scale_factor = exp((double)cam->zoom / 100.);
	cam->m.data[0][0] = scale_factor;
	cam->m.data[1][1] = scale_factor;
	cam->d = (t_mat){{
						   {2. / w, 0, 0, -1},
						   {0, -2. / w, 0, (double)h / w},
						   {0, 0, 1, 0},
						   {0, 0, 0, 1}}};
}

void t_cam_move(t_cam *cam, t_controller *c, double dt)
{
	double step;
	double scale_factor;

	cam->zoom += c->dz;
	scale_factor = exp((double)cam->zoom / 100.);
	step = dt * scale_factor * .6;
	cam->m.data[0][3] -= step * c->dx;
	cam->m.data[1][3] -= step * c->dy;
	cam->m.data[0][0] = scale_factor;
	cam->m.data[1][1] = scale_factor;
	cam->m.data[2][3] -= step * c->du;
}