/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/22 15:41:46 by hogu          #+#    #+#                 */
/*   Updated: 2025/09/26 15:49:57 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	to_byte(double c)
{
	clamp(&c, 0.0, 1.0);
	return ((int)(c * 255.0));
}

int	get_rgba(t_color col, double alpha)
{
	int r;
	int g;
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
	t_color col;

	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

t_color	multiply_color(t_color cl1, t_color cl2)
{
	return (color(cl1.r * cl2.r, cl1.g * cl2.g, cl1.b * cl2.b));


}

/*Sum two colors while not keeping the result as a valid color*/
// Not needed for now because I'm clamping all the way at the end anyways (to_byte)
// t_color	sum_col_notinrange(t_color cl1, t_color cl2)
// {
// 	t_color	new;

// 	new.r = cl1.r + cl2.r;
// 	new.g = cl1.g + cl2.g;
// 	new.b = cl1.b + cl2.b;
// 	return (new);
// }

/* sum the effect of 2 colors and make sure it is still in valid range*/
t_color	sum_color(t_color cl1, t_color cl2)
{
	t_color	ret;

	ret.r = cl1.r + cl2.r;
	ret.g = cl1.g + cl2.g;
	ret.b = cl1.b + cl2.b;
	// clamp(&ret.r, 0.0, 1.0);
	// clamp(&ret.g, 0.0, 1.0);
	// clamp(&ret.b, 0.0, 1.0);
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
	color.r = ((1 - a) * 255.0 + a * 25.0) / 255.0;
	color.g = ((1 - a) * 255.0 + a * 25.0) / 255.0;
	color.b = ((1 - a) * 255.0 + a * 112.0) / 255.0;
	return (color);
}
