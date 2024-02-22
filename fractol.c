/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 20:04:40 by saleshin          #+#    #+#             */
/*   Updated: 2024/02/21 20:04:45 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_window(void)
{
	exit (0);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY || keycode == ON_DESTROY)
	{
		if (keycode == ESC_KEY)
			mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
	if (keycode == ON_KEYUP)
		vars->julia_a = vars->julia_a + 0.1;
	if (keycode == ON_KEYDOWN)
		vars->julia_a = vars->julia_a - 0.1;
	if (keycode == ON_KEYLEFT)
		vars->julia_b = vars->julia_b - 0.1;
	if (keycode == ON_KEYRIGHT)
		vars->julia_b = vars->julia_b + 0.1;
	scan_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		vars->range_x = vars->range_x * 0.9;
		vars->range_y = vars->range_y * 0.9;
	}
	else if (button == 5)
	{
		vars->range_x = vars->range_x * 1.1;
		vars->range_y = vars->range_y * 1.1;
	}
	scan_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	scan_image(t_vars *vars)
{
	while (vars->y < vars->height)
	{
		vars->x = 0;
		while (vars->x < vars->width)
		{
			if (julia(vars) < vars->iteration) //mandelbrot(vars) < vars->iteration)
				put_pixel_to_image(vars, 0xFF0000);
			else
				put_pixel_to_image(vars, 0x000000);
			vars->x++;
		}
		vars->y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	vars->x = 0;
	vars->y = 0;
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.width = 800;
	vars.height = 600;
	vars.x = 0;
	vars.y = 0;
	vars.iteration = 100;
	vars.julia_a = -0.4;
	vars.julia_b = 0.6;
	vars.min_x = 0;
	vars.min_y = 0;
	vars.range_x = 1;
	vars.range_y = 1;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "Fractol");
	vars.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel,
			&vars.line_length, &vars.endian);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_hook(vars.win, 17, 0, close_window, NULL);
	mlx_hook(vars.win, 4, 0, mouse_hook, &vars);
	scan_image(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
