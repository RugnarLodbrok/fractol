#include "libft.h"
#include "fractol.h"
#include "mlx.h"
#include <time.h>

void update(t_app *app, double dt)
{
	(void)app;
	(void)dt;
}

int		loop_hook(t_app *app)
{
	double	dt;

	app->time = clock();
	dt = (double)(app->time - app->frame_time) / CLOCKS_PER_SEC;
	if (dt > FRAME_TIME)
	{
		app->frame_time = app->time;
		update(app, dt);
	}
	return (0);
}

int		close_hook(void *param)
{
	(void)param;
	exit(0);
}

int main()
{
	t_app app;

	t_app_init(&app);
//	print_info(&app);
	mlx_loop_hook(app.M, loop_hook, &app);
	mlx_hook(app.win, MLX_EVENT_EXIT, 0, &close_hook, 0);
	mlx_loop(app.M);
	return (0);
}
