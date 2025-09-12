/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 16:30:45 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/15 12:36:29 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double	len_vec(t_vec vec)
{
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (len);
}

t_vec	neg_vec(t_vec vec)
{
	return ((t_vec){-vec.x, -vec.y, -vec.z});
}

t_vec	scaled(t_vec vec, double s)
{
	return ((t_vec){vec.x * s, vec.y * s, vec.z * s});
}

t_vec	normalized(t_vec v)
{
	double	len;

	len = len_vec(v);
	if (len < EPSILON)
		return (vec(0, 0, 0));
	else
		return (scaled(v, 1 / len));
}
