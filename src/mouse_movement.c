#include <math.h>
#include "fractol.h"

void fractol_mouse_lmbc(t_controller *c, t_cam *cam)
{
	t_mat m;

	m = t_mat_mul_ref(&cam->m, &cam->d);
	cam->click_pos = t_vec_transform((t_vec){
			c->mouse.click_pos[MOUSE_B_LEFT].x,
			c->mouse.click_pos[MOUSE_B_LEFT].y,
			0
	}, &m);
}

void fractol_mouse_move(t_controller *c, t_cam *cam)
{
	t_vec pos;
	t_mat m;

	if (c->mouse.buttons[MOUSE_B_RIGHT])
	{
		cam->julia_offset.x = (double)c->mouse.pos.x / 100;
		cam->julia_offset.y = (double)c->mouse.pos.y / 500 - 1;
		cam->is_changed = 0xFFFFFFFF;
	}
	else if (c->mouse.buttons[MOUSE_B_LEFT])
	{
		m = t_mat_mul_ref(&cam->m, &cam->d);
		pos = t_vec_transform((t_vec){
				c->mouse.pos.x,
				c->mouse.pos.y,
				0
		}, &m);
		t_mat_translate(&cam->m, t_vec_sub(cam->click_pos, pos));
		cam->is_changed = 0xFFFFFFFF;
	}
}

static void zoom(t_controller *c, t_cam *cam, double v)
{
	t_mat m;
	t_mat mi;
	t_mat zoom_m;

	m = t_mat_mul_ref(&cam->m, &cam->d);
	mi = t_mat_inverted(m);
	t_mat_translate(&mi, (t_vec){-c->mouse.pos.x, -c->mouse.pos.y, 0});
	m = t_mat_inverted(mi);
	t_mat_reset(&zoom_m);
	zoom_m.data[0][0] = v;
	zoom_m.data[1][1] = v;
	zoom_m = t_mat_mul(zoom_m, mi);
	zoom_m = t_mat_mul(m, zoom_m);
	cam->m = (t_mat_mul(zoom_m, cam->m));
	cam->is_changed = 0xFFFFFFFF;
}

void fractol_mouse_wheel_up(t_controller *c, t_cam *cam)
{
	double scale;

	scale = 1 / exp(cam->zoom / 2.);
	cam->zoom -= ZOOM_STEP;
	scale *= exp(cam->zoom / 2.);
	zoom(c, cam, scale);
}

void fractol_mouse_wheel_down(t_controller *c, t_cam *cam)
{
	double scale;
	scale = 1 / exp(cam->zoom / 2.);
	cam->zoom += ZOOM_STEP;
	scale *= exp(cam->zoom / 2.);
	zoom(c, cam, scale);
}
