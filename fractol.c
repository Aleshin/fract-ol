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

void	put_pixel_to_image(t_vars *vars, int color)
{
	int	pixel;

	pixel = (vars->y * vars->line_length) + (vars->x * 4);
	if (vars->bits_per_pixel == 32)
	{
		vars->addr[pixel + 0] = (color >> 0) & 0xFF;
		vars->addr[pixel + 1] = (color >> 8) & 0xFF;
		vars->addr[pixel + 2] = (color >> 16) & 0xFF;
		vars->addr[pixel + 3] = (color >> 24) & 0xFF;
	}
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY || keycode == ON_DESTROY)
	{
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
	printf("key %d, julia_a = %f, julia_b = %f\n", keycode, vars->julia_a, vars->julia_b);
    scan_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

void	pixel_to_complex(t_vars *vars)
{
	double	min_x;
	double	min_y;
	double	range_x;
	double	range_y;

	min_x = -2;
	min_y = -2;
	range_x = 4;
	range_y = 4;
	vars->a = vars->x * (range_x / vars->width) + min_x;
	vars->b = vars->y * (range_y / vars->height) + min_y;
}

int	scan_image(t_vars *vars)
{
	while (vars->y < vars->height)
	{
		vars->x = 0;
		while (vars->x < vars->width)
		{
			if (julia(vars) < vars->iteration) //mandelbrot(vars) < vars->iteration)
			{
				put_pixel_to_image(vars, 0xFF0000);
			}
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
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "Fractol");
	vars.img = mlx_new_image(vars.mlx, vars.width, vars.height);
	vars.addr = mlx_get_data_addr(vars.img, &vars.bits_per_pixel,
			&vars.line_length, &vars.endian);
	mlx_key_hook(vars.win, key_press, &vars);
	scan_image(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
