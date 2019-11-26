#include <time.h>
#include <math.h>
#include "mlx.h"
#include "fractol.h"

static void t_view_init(t_view *v, int w, int h)
{
	t_mat_reset(&v->m);
	v->m.data[0][0] = 2;
	v->m.data[1][1] = 2;
	v->d = (t_mat){{
							{2. / w, 0, 0, -1},
							{0, -2. / w, 0, (double)h / w},
							{0, 0, 1, 0},
							{0, 0, 0, 1}}};
}

void t_view_move(t_view *v, t_controller *c, double dt)
{
	double z;
	double step;

	v->zoom += c->dz;
	z = exp((double)v->zoom / 100.);
	step = dt * z * .6;
	v->m.data[0][3] -= step * c->dx;
	v->m.data[1][3] -= step * c->dy;
	v->m.data[0][0] = z;
	v->m.data[1][1] = z;
	v->m.data[2][3] -= step * c->du;
}

static int close_hook(void *param)
{
	(void)param;
	exit(0);
}

static int loop_hook(t_app *app)
{
	double dt;

	app->time = clock();
	dt = (double)(app->time - app->frame_time) / CLOCKS_PER_SEC;
	if (dt > FRAME_TIME)
	{
		app->frame_time = app->time;
		app->update(app, dt);
	}
	return (0);
}

void t_app_init(t_app *app, void (*update)(t_app *app, double dt))
{
	ft_bzero(app, sizeof(t_app));
	app->w = WIN_W;
	app->h = WIN_H;
	app->sidebar_w = 0;
	app->time = clock();
	app->frame_time = app->time;
	app->update = update;
	t_view_init(&app->view, app->w, app->h);
	app->M = mlx_init();
	app->win = mlx_new_window(app->M, app->sidebar_w + app->w, app->h, "fdf");
	mlx_bind_keys(app->win, &app->controller);
	t_framebuffer_init(&app->framebuffer, app->M, app->w, app->h);
}

void t_app_run(t_app *app)
{

	mlx_loop_hook(app->M, loop_hook, app);
	mlx_hook(app->win, MLX_EVENT_EXIT, 0, &close_hook, 0);
	mlx_bind_keys(app->win, &app->controller);
	mlx_loop(app->M);

}