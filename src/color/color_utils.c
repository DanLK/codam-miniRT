/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/22 15:41:46 by hogu          #+#    #+#                 */
/*   Updated: 2025/10/22 13:36:53 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	clamp(double *num, double min, double max)
{
	if (*num < min)
		*num = min;
	else if (*num > max)
		*num = max;
}

//sqrt for gamma correction
static int	to_byte(double c)
{
	clamp(&c, 0.0, 1.0);
	c = sqrt(c);
	return ((int)(c * 255.0));
}

int	get_rgba(t_color col, double alpha)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = to_byte(col.r);
	g = to_byte(col.g);
	b = to_byte(col.b);
	a = to_byte(alpha);
	return (r << 24 | g << 16 | b << 8 | a);
}

t_color	color(double r, double g, double b)
{
	t_color	col;

	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

/* Depicts a gradient in y from blue to white*/
t_color	calc_background_color(t_ray ray)
{
	t_color	color;
	t_vec	unit_dir;
	double	a;

	unit_dir = normalized(ray.dir);
	a = 0.5 * (unit_dir.y + 1.0);
	color.r = ((1 - a) * 255.0 + a * 25.0) / 255.0;
	color.g = ((1 - a) * 255.0 + a * 25.0) / 255.0;
	color.b = ((1 - a) * 255.0 + a * 112.0) / 255.0;
	return (color);
}
