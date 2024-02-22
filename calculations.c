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

int	mandelbrot(t_vars *vars)
{
	double	x;
	double	y;
	double	temp;
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
