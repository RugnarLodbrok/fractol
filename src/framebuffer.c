
#include "mlx.h"
#include "libft.h"
#include "fractol.h"

static uint blend_alpha(uint c1, uint c2, uint a)
{
	uint c;
	uint res;

	c1 &= 0xFFFFFF;
	c2 &= 0xFFFFFF;
	res = 0;
	c = (c1 & 0x0000FF) * (255 - a) + (c2 & 0x0000FF) * a;
	c /= 255;
	res += c;
	c = ((c1 & 0x00FF00) >> 8) * (255 - a) + ((c2 & 0x00FF00) >> 8) * a;
	c /= 255;
	res += c << 8;
	c = ((c1 & 0xFF0000) >> 16) * (255 - a) + ((c2 & 0xFF0000) >> 16) * a;
	c /= 255;
	res += c << 16;
	return (res);
}

void t_framebuffer_init(t_framebuffer *fb, void *mlx, int w, int h)
{
	fb->image = mlx_new_image(mlx, WIN_W, WIN_H);
	fb->data = (uint *)mlx_get_data_addr(
			fb->image,
			&fb->bpp,
			&fb->row_len,
			&fb->endian);
	fb->bpp /= 8;
	fb->row_len /= fb->bpp;
	fb->w = w;
	fb->h = h;
}

void t_framebuffer_clear(t_framebuffer *fb)
{
	(void)fb;
	ft_bzero(fb->data, fb->row_len * WIN_H * sizeof(int));
}

void fb_put_pixel(t_framebuffer *fb, int x, int y, uint color)
{

	if (x < 0 || y < 0 || x >= fb->w || y >= fb->h)
		return;
	fb->data[y * fb->row_len + x] = color;
}

void fb_put_pixel_alpha(t_framebuffer *fb, int x, int y, uint color)
{
	unsigned char a;
	uint *d;

	if (x < 0 || y < 0 || x >= fb->w || y >= fb->h)
		return;
	a = color >> 24;
	d = &fb->data[y * fb->row_len + x];
	*d = blend_alpha(*d, color, a);
}
