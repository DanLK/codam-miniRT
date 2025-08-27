/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_ops.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 12:18:25 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/15 12:38:05 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	sum_vec(t_vec u, t_vec v)
{
	t_vec	sum;

	sum.x = u.x + v.x;
	sum.y = u.y + v.y;
	sum.z = u.z + v.z;
	return (sum);
}

t_vec	*sum_vec_new(t_vec u, t_vec v)
{
	t_vec	*sum;

	sum = init_vec(u.x + v.x, u.y + v.y, u.z + v.z);
	if (!sum)
		return (NULL);
	return (sum);
}

double	dot(t_vec u, t_vec v)
{
	double	dot;

	dot = u.x * v.x + u.y * v.y + u.z * v.z;
	return (dot);
}

t_vec	cross(t_vec u, t_vec v)
{
	t_vec	cross;

	cross.x = u.y * v.z - u.z * v.y;
	cross.y = u.z * v.x - u.x * v.z;
	cross.z = u.x * v.y - u.y * v.x;
	return (cross);
}

t_vec	sub_vec(t_vec u, t_vec v)
{
	t_vec	diff;

	diff.x = u.x - v.x;
	diff.y = u.y - v.y;
	diff.z = u.z - v.z;
	return (diff);
}
