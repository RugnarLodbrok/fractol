#ifndef FRACTOL_H
# define FRACTOL_H

# define WIN_W 1200
# define WIN_H 800
# define FRAME_RATE 10
# define FRAME_TIME 1./FRAME_RATE

# define ZOOM_STEP 1

# define MAX_ITER 4096
# define DEFAULT_LOD 3

# define FRACTOL_MAND 0
# define FRACTOL_JULIA 1

# define FRACTOL_Z2 0
# define FRACTOL_SIN 2

# define FRACTOL_MAND_Z2 (FRACTOL_MAND | FRACTOL_Z2)
# define FRACTOL_MAND_SIN (FRACTOL_MAND | FRACTOL_SIN)
# define FRACTOL_JULIA_Z2 (FRACTOL_JULIA | FRACTOL_Z2)
# define FRACTOL_JULIA_SIN (FRACTOL_JULIA | FRACTOL_SIN)

# define HELP1 "Usage: ./fractol TYPE\n\twhere TYPE is one of following:\n"
# define HELP2 "\t- mandelbrot\n\t- julia\n\t- mandelbrot_sin\n\t- julia_sin"
# define HELP HELP1 HELP2

#include "libft.h"
#include "ft_linalg.h"
#include "threading.h"
#include "mlx_consts.h"

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
	void *p;
	void (*f)(void *c, void *p);
} t_control_callback;

typedef struct
{
	int buttons[8];
	t_point pos;
	t_point click_pos[8];
	t_point release_pos[8];
	t_control_callback bindings[8];
	t_control_callback move_bind;
} t_mouse;

typedef struct
{
	char keyboard[128];
	t_control_callback keyboard_bindings[128];
	t_mouse	mouse;
	int dx;
	int dy;
	int du;
	int dv;
	int dz;
	int d_yaw;

} t_controller;

typedef struct
{
	uint is_changed;
	t_vec julia_offset;
	double zoom;
	double rot_angle;
	t_mat m; //model-view for re axis
	t_vec click_pos; //used for mouse movement
	t_mat d; //display
} t_cam;

typedef struct
{
	t_complex z;
	t_complex c;
	uint i;
	int stop;
} t_fractol_pix;

typedef struct
{
	int size;
	int *data;
} t_it_estimator;

typedef struct
{
	int w;
	int h;
	uint *color_cache;
	int lod;
	uint stop_count;
	int (*func_iter)(t_fractol_pix *p);
	void (*func_reset)(t_fractol_pix *p, t_complex z, t_complex c);
	t_it_estimator ies;
	t_fractol_pix *data;
} t_fractol;

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
	t_cam cam;
	t_fractol fractol;
	void (*update)(struct s_app *app, double dt);
	int shutdown;
} t_app;

void t_app_init(t_app *app, void (*update)(t_app *app, double dt));
void t_app_up(t_app *app);
void t_app_run(t_app *app);
void bind_keys(void *win, t_controller *c);
void t_ctrl_bind(t_controller *c, int key_code, void (*f)(), void *p);
void t_ctrl_mouse_bind(t_controller *c, int key_code, void (*f)(), void *p);

void t_framebuffer_init(t_framebuffer *fb, void *mlx, int w, int h);
void t_framebuffer_clear(t_framebuffer *fb);
void fb_put_pixel(t_framebuffer *fb, int x, int y, uint color);

void t_cam_init(t_cam *cam, int w, int h);
void t_cam_move(t_cam *cam, t_controller *c, double dt);

uint hue_spiral(int iteration);

void t_fractol_pix_reset_julia(t_fractol_pix *pix, t_complex z, t_complex c);
void t_fractol_pix_reset_mand(t_fractol_pix *pix, t_complex z, t_complex c);
int t_fractol_pix_z2(t_fractol_pix *p);
int t_fractol_pix_sin(t_fractol_pix *p);

void t_fractol_init(t_fractol *f, int w, int h, int fractol_type);
void t_fractol_reset(t_fractol *f, t_cam *cam, t_thread_id ti);
void t_fractol_draw(t_fractol *f, t_framebuffer *fb);
void t_fractol_iteration(t_fractol *f, t_thread_id ti);

void t_ies_init(t_it_estimator *ies);
void t_ies_add(t_it_estimator *ies, int i);
int t_ies_estimate(t_it_estimator *ies);
void t_ies_reset(t_it_estimator *ies);

void fractol_mouse_lmbc(t_controller *c, t_cam *cam);
void fractol_mouse_move(t_controller *c, t_cam *cam);
void fractol_mouse_wheel_up(t_controller *c, t_cam *cam);
void fractol_mouse_wheel_down(t_controller *c, t_cam *cam);

#endif
