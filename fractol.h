#ifndef FRACTOL_H
# define FRACTOL_H

# define WIN_W 800
# define WIN_H 600
# define FRAME_RATE 120
# define FRAME_TIME 1./FRAME_RATE

# define MLX_EVEN_KEY_PRESS 2
# define MLX_EVEN_KEY_RELEASE 3
# define MLX_EVENT_EXIT 17

#ifdef _WIN32
# define RED 0x1
# define GREEN 0x100
# define BLUE 0x10000
#else
# define RED 0x10000
# define GREEN 0x100
# define BLUE 0x1
#endif
# define ALPHA 0x1000000
# define GRAYSCALE 0x010101
# define WHITE 0xffffff


# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_ESC 53
# define KEY_I 34
# define KEY_P 35
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_HOME 115
# define KEY_END 119

#include "libft.h"
#include "ft_linalg.h"

typedef struct
{
	double re;
	double im;
} t_complex;

typedef struct
{
	int w;
	int h;
	void *image;
	uint *data;
	int bpp;
	int endian;
	int row_len;
} t_framebuffer;

typedef struct
{
	int keyboard[128];
	int dx;
	int dy;
	int dz;
} t_controller;

typedef struct
{
	t_mat m; //model-view
	t_mat d; //display
	t_mat mi;
	t_mat di;
} t_view;

typedef struct s_app t_app;

typedef struct s_app
{
	int w;
	int h;
	int sidebar_w;
	void *M;
	void *win;
	t_framebuffer framebuffer;
	time_t time;
	time_t frame_time;
	t_controller controller;
	t_view view;
	void (*update)(t_app *app, double dt);
	int shutdown;
} t_app;

void t_app_init(t_app *app, void (*update)(t_app *app, double dt));
void t_app_run(t_app *app);
void mlx_bind_keys(void *win, t_controller *c);
void t_framebuffer_init(t_framebuffer *fb, void *mlx, int w, int h);
void t_framebuffer_clear(t_framebuffer *fb);
void fb_put_pixel(t_framebuffer *fb, int x, int y, uint color);
void t_view_move(t_view *v, t_controller *c);
uint hue_spiral(int iteration);

#endif
