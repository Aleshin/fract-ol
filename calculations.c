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

void	pixel_to_complex(t_vars *vars)
{
	vars->a = vars->x * (vars->width_a / vars->width) + vars->a0;
	vars->b = vars->y * (vars->height_b / vars->height) + vars->b0;
}

int	color(t_vars *vars, int iterations)
{
	double	t;
	int		color;

	t = (double)iterations / (double)vars->iteration;
	color = 0;
	color = color << 8;
	color += (unsigned char)(vars->colors[0] * (1 - t) * t * t * t * 255);
	color = color << 8;
	color += (unsigned char)(vars->colors[1] * (1 - t) * (1 - t) * t * t * 255);
	color = color << 8;
	color += (unsigned char)(vars->colors[2] * (1 - t) * (1 - t) * (1 - t)
			* t * 255);
	return (color);
}

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

int	mandelbrot(t_vars *vars)
{
	long double	x;
	long double	y;
	long double	temp;
	int		i;

	x = 0;
	y = 0;
	i = 0;
	pixel_to_complex(vars);
	while (x * x + y * y <= 2 * 2 && i < vars->iteration)
	{
		temp = x * x - y * y + vars->a;
		y = 2 * x * y + vars->b;
		x = temp;
		i++;
	}
	return (i);
}

int	julia(t_vars *vars)
{
	double	x;
	double	y;
	double	temp;
	int		i;

	pixel_to_complex(vars);
	x = vars->a;
	y = vars->b;
	i = 0;
	while (x * x + y * y <= 2 * 2 && i < vars->iteration)
	{
		temp = x * x - y * y + vars->julia_a;
		y = 2 * x * y + vars->julia_b;
		x = temp;
		i++;
	}
	return (i);
}
