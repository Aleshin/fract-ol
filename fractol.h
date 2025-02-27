/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 23:02:32 by saleshin          #+#    #+#             */
/*   Updated: 2024/02/21 23:02:36 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define ESC_KEY 53
#define ON_KEYLEFT 123
#define ON_KEYRIGHT 124
#define ON_KEYDOWN 125
#define ON_KEYUP 126
#define ON_DESTROY 17
#define COLORS 3

typedef struct s_vars	t_vars;
typedef int				(*t_function_pointer)(t_vars *);
typedef struct s_vars
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					iteration;
	int					x;
	int					y;
	double				a;
	double				b;
	double				julia_a;
	double				julia_b;
	int					width;
	int					height;
	double				a0;
	double				b0;
	double				width_a;
	double				height_b;
	int					mouse_drag;
	int					mouse_x;
	int					mouse_y;
	int					colors[COLORS];
	t_function_pointer	f_pointer;
}	t_vars;

void	put_pixel_to_image(t_vars *vars, int color);
int		color(t_vars *vars, int iterations);
int		close_window(void);
int		key_press(int keycode, t_vars *vars);
int		mouse_hook(int button, int x, int y, t_vars *vars);
int		mouse_wheel(int button, int x, int y, t_vars *vars);
int		mouse_move(int x, int y, t_vars *vars);
int		mouse_release(int button, int x, int y, t_vars *vars);
void	pixel_to_complex(t_vars *vars);
int		mandelbrot(t_vars *vars);
int		julia(t_vars *vars);
int		scan_image(t_vars *vars);
