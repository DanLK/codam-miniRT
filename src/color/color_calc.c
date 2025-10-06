/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   color_calc.c                                        :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/10/01 11:39:13 by hogu           #+#    #+#                */
/*   Updated: 2025/10/01 11:39:14 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	col_mul(t_color cl1, t_color cl2)
{
	return (color(cl1.r * cl2.r, cl1.g * cl2.g, cl1.b * cl2.b));
}

t_color	col_sum(t_color cl1, t_color cl2)
{
	t_color	ret;

	ret.r = cl1.r + cl2.r;
	ret.g = cl1.g + cl2.g;
	ret.b = cl1.b + cl2.b;
	return (ret);
}

t_color	col_scale(t_color cl, double scalar)
{
	t_color	new;

	new.r = cl.r * scalar;
	new.g = cl.g * scalar;
	new.b = cl.b * scalar;
	return (new);
}
