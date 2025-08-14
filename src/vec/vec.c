/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 16:30:45 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/14 17:11:12 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "unistd.h"

t_vec	*init_vec(double x, double y, double z)
{
	t_vec	*vec;

	vec = malloc(sizeof(t_vec));
	if (!vec)
		return (NULL);
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

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

void	neg_vec(t_vec *vec)
{
	vec->x = -vec->x;
	vec->y = -vec->y;
	vec->z = -vec->z;
}

t_vec	neg_vec_new(t_vec vec)
{
	t_vec neg;

	neg = vec;
	neg_vec(&neg);
	return (neg);
}

void	scale_vec(t_vec *vec, double scalar)
{
	vec->x *= scalar;
	vec->y *= scalar;
	vec->z *= scalar;
}

t_vec	scaled(t_vec vec, double scalar)
{
	t_vec	scaled;

	if (scalar != 0)
	{
		scaled.x = vec.x * scalar;
		scaled.y = vec.y * scalar;
		scaled.z = vec.z * scalar;
	}
	else //Don't really know how to handle this case
	{
		scaled.x = 0;
		scaled.y = 0;
		scaled.z = 0;
	}
	return (scaled);
}

void	normalize(t_vec v)
{
	double	len;

	len = len_vec(v);
	if (len != 0)
		scale_vec(&v, 1 / len);
}

t_vec	normalized(t_vec v)
{
	double	len;

	len = len_vec(v);
	if (len != 0)
		return (scaled(v, 1 / len));
	else
		return (vec(0, 0, 0)); //Not sure what to do in this error case
}
