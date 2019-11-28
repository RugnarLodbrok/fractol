#include <math.h>
#include "fractol.h"

void t_cam_init(t_cam *cam, int w, int h)
{
	double scale_factor;

	t_mat_reset(&cam->m);
	t_mat_reset(&cam->rot);
	cam->zoom = 0;
	cam->rot_angle = 0;
	cam->is_changed = 1;
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

	cam->is_changed = 0;
	if (c->du || c->dx || c->dy || c->dv || c->dz || c->d_yaw)
		cam->is_changed = 1;
	cam->zoom += c->dz;
	cam->rot_angle += c->d_yaw;
	scale_factor = exp((double)cam->zoom / 100.);
	step = dt * scale_factor * .6;
	cam->m.data[0][3] -= step * c->dx;
	cam->m.data[1][3] -= step * c->dy;
	cam->m.data[0][0] = scale_factor;
	cam->m.data[1][1] = scale_factor;
	ft_printf("dyaw: %d\n", c->d_yaw);
	if (c->d_yaw)
		cam->rot = t_mat_rot((t_vec){0, 0, 1},
							 ((double)cam->rot_angle) / 64);
}
