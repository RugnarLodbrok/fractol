#include <math.h>
#include "fractol.h"

void t_cam_init(t_cam *cam, int w, int h)
{
	double scale_factor;

	t_mat_reset(&cam->m);
	cam->zoom = 0;
	cam->rot_angle = 0;
	cam->is_changed = 0xFFFFFFFF;
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

	if (!(c->dx || c->dy || c->du || c->dv || c->dz || c->d_yaw))
		return;
	cam->zoom += dt * c->dz;
	cam->julia_offset.x += dt * c->du * .2;
	cam->julia_offset.y += dt * c->dv * .01;
	scale_factor = exp(cam->zoom / 2.);
	step = dt * scale_factor * .6;
	cam->m.data[0][3] -= step * c->dx;
	cam->m.data[1][3] -= step * c->dy;
	cam->m.data[0][0] = scale_factor;
	cam->m.data[1][1] = scale_factor;
	if (c->d_yaw)
		cam->rot_angle += dt * 10. * c->d_yaw;
	cam->is_changed = 0xFFFFFFFF;
}
