/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/22 15:41:46 by hogu          #+#    #+#                 */
/*   Updated: 2025/09/15 10:49:47 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	color(int r, int g, int b)
{
	t_color col;

	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

/*Sum two colors while not keeping the result as a valid color*/
t_color	sum_col_notinrange(t_color cl1, t_color cl2)
{
	t_color	new;

	new.r = cl1.r + cl2.r;
	new.g = cl1.g + cl2.g;
	new.b = cl1.b + cl2.b;
	return (new);
}

/* sum the effect of 2 colors and make sure it is still in valid range*/
t_color	sum_color(t_color cl1, t_color cl2)
{
	t_color	ret;

	ret.r = cl1.r + cl2.r;
	ret.g = cl1.g + cl2.g;
	ret.b = cl1.b + cl2.b;
	ret.r = fmin(ret.r, 255);
	ret.g = fmin(ret.g, 255);
	ret.b = fmin(ret.b, 255);
	return (ret);
}

t_color	scale_col(t_color cl, double scalar)
{
	t_color	new;

	new.r = cl.r * scalar;
	new.g = cl.g * scalar;
	new.b = cl.b * scalar;
	return (new);
	//Should add some error handling (?)
}

/* Depicts a gradient in y from blue to white*/
t_color	calc_background_color(t_ray ray)
{
	t_color	color;
	t_vec	unit_dir;
	double	a;

	unit_dir = normalized(ray.dir);
	a = 0.5 * (unit_dir.y + 1.0);
	color.r = (1 - a) * 255 + a * 25;
	color.g = (1 - a) * 255 + a * 25;
	color.b = (1 - a) * 255 + a * 112;
	return (color);
}
