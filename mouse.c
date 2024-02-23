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

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	double	ratio_x;
	double	ratio_y;

	ratio_x = x / vars->width;
	ratio_y = y / vars->height;
	if (button == 1)
	{
		vars->mouse_drag = 1;
		vars->mouse_x = x;
		vars->mouse_y = y;
	}
	if (button == 4 || button == 5)
		mouse_wheel(button, x, y, vars);
	return (0);
}

int	mouse_wheel(int button, int x, int y, t_vars *vars)
{
	double	ratio_x;
	double	ratio_y;

	ratio_x = (double)x / (double)vars->width;
	ratio_y = (double)y / (double)vars->height;
	if (button == 4)
	{
		vars->a0 = vars->a0 + 0.1 * vars->width_a * ratio_x;
		vars->width_a = vars->width_a * 0.9;
		vars->b0 = vars->b0 + 0.1 * vars->height_b * ratio_y;
		vars->height_b = vars->height_b * 0.9;
	}
	else if (button == 5)
	{
		vars->a0 = vars->a0 - 0.1 * vars->width_a * ratio_x;
		vars->width_a = vars->width_a * 1.1;
		vars->b0 = vars->b0 - 0.1 * vars->height_b * ratio_y;
		vars->height_b = vars->height_b * 1.1;
	}
	scan_image(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}

int	mouse_move(int x, int y, t_vars *vars)
{
	double	w;
	double	h;

	w = vars->width_a / vars->width;
	h = vars->height_b / vars->height;
	if (vars->mouse_drag == 1)
	{
		vars->a0 += (double)(vars->mouse_x - x) * w;
		vars->b0 += (double)(vars->mouse_y - y) * h;
		scan_image(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
		vars->mouse_x = x;
		vars->mouse_y = y;
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_vars *vars)
{
	(void)x;
	(void)y;
	if (button == 1)
		vars->mouse_drag = 0;
	return (0);
}
