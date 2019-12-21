#include <time.h>
#include "mlx.h"
#include "fractol.h"

static int close_hook(void *param)
{
	(void)param;
	ft_printf("EXIT\n");
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
	t_cam_init(&app->cam, app->w, app->h);
}

void t_app_up(t_app *app)
{
	app->M = mlx_init();
	app->win = mlx_new_window(app->M, app->sidebar_w + app->w, app->h, "fdf");
	bind_keys(app->win, &app->controller);
	t_framebuffer_init(&app->framebuffer, app->M, app->w, app->h);
}

void t_app_run(t_app *app)
{

	mlx_loop_hook(app->M, loop_hook, app);
	mlx_hook(app->win, MLX_EVENT_EXIT, 0, &close_hook, 0);
	bind_keys(app->win, &app->controller);
	mlx_loop(app->M);

}