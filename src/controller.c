/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:45:11 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/22 16:46:46 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fractol.h"

void t_controller_update_state(t_controller *c)
{
	c->dx = c->keyboard[KEY_A] - c->keyboard[KEY_D];
	c->dy = c->keyboard[KEY_S] - c->keyboard[KEY_W];
	c->dz = c->keyboard[KEY_Q] - c->keyboard[KEY_E];
	c->du = c->keyboard[KEY_LEFT] - c->keyboard[KEY_RIGHT];
	c->dv = c->keyboard[KEY_DOWN] - c->keyboard[KEY_UP];
	c->d_yaw = c->keyboard[KEY_Z] - c->keyboard[KEY_X];
}

void t_ctrl_bind(t_controller *c, int key_code, void (*f)(), void *p)
{
	c->keyboard_bindings[key_code].f = f;
	c->keyboard_bindings[key_code].p = p;
}

void t_ctrl_mouse_bind(t_controller *c, int key_code, void (*f)(), void *p)
{
	c->mouse.bindings[key_code].f = f;
	c->mouse.bindings[key_code].p = p;
}

int t_controller_key_press(int keycode, t_controller *c)
{
	if (keycode == KEY_ESC)
		exit(0);
	c->keyboard[keycode] = 1;
	if (c->keyboard_bindings[keycode].f)
		c->keyboard_bindings[keycode].f(c, c->keyboard_bindings[keycode].p);
	t_controller_update_state(c);
	return (0);
}

int t_controller_key_release(int keycode, t_controller *c)
{
	c->keyboard[keycode] = 0;
	t_controller_update_state(c);
	return (0);
}

static int t_controller_mouse_press(int button, int x, int y, t_controller *c)
{
	if (y < 0)
		return (0);
	c->mouse.buttons[button] = 1;
	c->mouse.click_pos[button] = (t_point){x, y};
	if (c->mouse.bindings[button].f)
		c->mouse.bindings[button].f(c, c->mouse.bindings[button].p);
	return (0);
}

static int t_controller_mouse_release(int button, int x, int y, t_controller *c)
{
	c->mouse.buttons[button] = 0;
	c->mouse.release_pos[button] = (t_point){x, y};
	return (0);
}

static int t_controller_mouse_move(int x, int y, t_controller *c)
{
	c->mouse.pos = (t_point){x, y};
	if (c->mouse.move_bind.f)
		c->mouse.move_bind.f(c, c->mouse.move_bind.p);
	return (0);
}

void bind_keys(void *win, t_controller *c)
{
	mlx_hook(win, MLX_EVENT_KEY_PRESS, 0, t_controller_key_press, c);
	mlx_hook(win, MLX_EVENT_KEY_RELEASE, 0, t_controller_key_release, c);
	mlx_hook(win, MLX_EVENT_MOUSE_PRESS, 0, t_controller_mouse_press, c);
	mlx_hook(win, MLX_EVENT_MOUSE_RELEASE, 0, t_controller_mouse_release, c);
	mlx_hook(win, MLX_EVENT_MOUSE_MOVE, 0, t_controller_mouse_move, c);
}
