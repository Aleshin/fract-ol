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

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
	if (keycode == ON_KEYUP)
		vars->julia_a = vars->julia_a + 0.05;
	else if (keycode == ON_KEYDOWN)
		vars->julia_a = vars->julia_a - 0.05;
	else if (keycode == ON_KEYLEFT)
		vars->julia_b = vars->julia_b - 0.05;
	else if (keycode == ON_KEYRIGHT)
		vars->julia_b = vars->julia_b + 0.05;
	else
		vars->colors[keycode % 3] = keycode;
	scan_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

void	man(void)
{
	write(1, "\nProgram's parameter:\n", 22);
	write(1, "[1] - Mandelbrot\n", 17);
	write(1, "[2] - Julia\n\n", 13);
	write(1, "Program's controls:\n", 20);
	write(1, "[any key] - change color scheme\n", 32);
	write(1, "[Up/Dn] - change a for Julia\n", 29);
	write(1, "[Left/Right] - change b for Julia\n", 34);
	write(1, "[Mouse wheel] - zoom in/zoom out\n", 33);
	write(1, "[Drag&Drop] - move\n\n", 20);
}

void	init(t_vars *vars)
{
	vars->width = 800;
	vars->height = 800;
	vars->x = 0;
	vars->y = 0;
	vars->iteration = 100;
	vars->julia_a = -0.4;
	vars->julia_b = 0.6;
	vars->a0 = -2;
	vars->b0 = -2;
	vars->width_a = 4;
	vars->height_b = 4;
	vars->mouse_drag = 0;
	vars->mlx = mlx_init();
	vars->colors[0] = 10;
	vars->colors[1] = 101;
	vars->colors[2] = 200;
	vars->win = mlx_new_window(vars->mlx, vars->width, vars->height, "Fractol");
	vars->img = mlx_new_image(vars->mlx, vars->width, vars->height);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
}

int	scan_image(t_vars *vars)
{
	int	iteractions;

	while (vars->y < vars->height)
	{
		vars->x = 0;
		while (vars->x < vars->width)
		{
			iteractions = vars->f_pointer(vars);
			if (iteractions < vars->iteration)
				put_pixel_to_image(vars, color(vars, iteractions));
			else
				put_pixel_to_image(vars, 0x00F0F0F0);
			vars->x++;
		}
		vars->y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	vars->x = 0;
	vars->y = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
	{
		man();
		return (0);
	}
	if (argv[1][0] == '1' && argv[1][1] == '\0')
		vars.f_pointer = mandelbrot;
	else if (argv[1][0] == '2' && argv[1][1] == '\0')
		vars.f_pointer = julia;
	else
	{
		man();
		return (0);
	}
	init(&vars);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_hook(vars.win, 17, 0, close_window, NULL);
	mlx_hook(vars.win, 4, 0, mouse_hook, &vars);
	mlx_hook(vars.win, 6, 0, mouse_move, &vars);
	mlx_hook(vars.win, 5, 0, mouse_release, &vars);
	scan_image(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
