#include "mlx.h"
#include "fractol.h"
#include <time.h>

void t_app_init(t_app *app)
{
	ft_bzero(app, sizeof(t_app));
	app->w = WIN_W;
	app->h = WIN_H;
	app->time = clock();
	app->frame_time = app->time;
	app->M = mlx_init();
	app->win = mlx_new_window(app->M, app->sidebar_w + app->w, app->h, "fdf");
	mlx_bind_keys(app->win, &app->controller);
	t_framebuffer_init(&app->framebuffer, app->M, app->w, app->h);
}
