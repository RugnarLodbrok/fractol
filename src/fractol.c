#include "fractol.h"
#include <math.h>

/*
 * todo: sin(z) + c?
*/

void t_fractol_init(t_fractol *f, int w, int h)
{
	int i;

	f->w = w;
	f->h = h;
	f->data = ft_memalloc(sizeof(t_fractol_pix) * w * h);
	f->color_cache = malloc(sizeof(uint) * MAX_ITER);
	f->lod = DEFAULT_LOD;
	f->stop_count = 0;
	i = -1;
	while (++i < MAX_ITER)
		f->color_cache[i] = hue_spiral(i);
	t_ies_init(&f->ies);
}

static void iterate_pixel(t_fractol *f, int i, int j)
{
	uint k;
	t_fractol_pix *p;

	p = &f->data[f->w * j + i];
	if (p->stop)
		return;
	k = (p->i << 2) + 1;
	if (k > 0x20)
		k = 0x20;
	while (k--)
		if (t_fractol_pix_z2(p) == INT_MAX)
		{
			f->stop_count++;
			t_ies_add(&f->ies, p->i);
			break;
		}
}

void t_fractol_iteration(t_fractol *f, t_thread_id ti)
{
	int i;
	int j;
	int lod_step = (1 << f->lod);
	int j_step = lod_step;
	int i_step = lod_step * ti.c;
	//todo: make benchmark to see how much struct field access costs;

	for (i = ti.i * lod_step; i < f->w; i += i_step)
		for (j = 0; j < f->h; j += j_step)
			iterate_pixel(f, i, j);
}

static void next_lod_check(t_fractol *f)
{
	uint threshold;

	if (!f->lod)
		return;
	threshold = (f->w * f->h) >> (2 * f->lod);
	threshold >>= 2;
	if (f->stop_count > threshold)
		f->lod--;
}

void t_fractol_draw(t_fractol *f, t_framebuffer *fb)
{
	int i;
	int j;
	t_fractol_pix *p;
	int it_estimation;
	uint mask = (0xFFFFFFFF >> f->lod) << f->lod;

	it_estimation = t_ies_estimate(&f->ies);
	for (i = 0; i < f->w; i++)
	{
		for (j = 0; j < f->h; j++)
		{
			p = &f->data[(j & mask) * f->w + (i & mask)];
			if (p->stop)
				fb->data[j * f->w + i] = f->color_cache[p->i];
			else if (p->i > it_estimation)
				fb->data[j * f->w + i] = 0;
		}
	}
	next_lod_check(f);
}

static void rotate_m_to_j(t_vec *z, t_vec *c, double a)
{
	t_vec tmp;
	double si;
	double co;

	si = sin(a);
	co = cos(a);
	tmp = (t_vec){z->x, c->x};
	z->x = tmp.x * co + tmp.y * si;
	c->x = -tmp.x * si + tmp.y * co;
	tmp = (t_vec){z->y, c->y};
	z->y = tmp.x * co + tmp.y * si;
	c->y = -tmp.x * si + tmp.y * co;
}

void t_fractol_reset(t_fractol *f, t_cam *cam, t_thread_id ti)
{
	int i;
	int j;
	int w;
	t_mat m;
	t_vec z;
	t_vec c;
	double angle;
	double julia_offset;
	int lod_step = (1 << 0);
	int j_step = lod_step;
	int i_step = lod_step * ti.c;

	m = t_mat_mul_ref(&cam->m, &cam->d);
	w = f->w;
	if (!ti.i)
	{
		f->stop_count = 0;
		f->lod = DEFAULT_LOD;
		t_ies_reset(&f->ies);
	}
	angle = cam->rot_angle / 100;
	julia_offset = exp(cam->julia_offset.x) * .6357;
	for (i = ti.i * lod_step; i < f->w; i += i_step)
	{
		for (j = 0; j < f->h; j += j_step)
		{
			c = t_vec_transform((t_vec){i, j}, m);
			z = (t_vec){0, julia_offset * sin(angle), 0};
			rotate_m_to_j(&z, &c, angle);
			t_fractol_pix_reset(&f->data[j * w + i],
								*(t_complex *)&z,
								*(t_complex *)&c);
		}
	}
}
