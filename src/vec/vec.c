/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 16:30:45 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/11 12:20:44 by dloustal      ########   odam.nl         */
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

double	len_vec(t_vec *vec)
{
	double	len;
	if (!vec)
		return (-1);
	len = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	return (len);
}

void	neg_vec(t_vec *vec)
{
	if (!vec)
		return ;
	vec->x = -vec->x;
	vec->y = -vec->y;
	vec->z = -vec->z;
}

void	scale_vec(t_vec *vec, double scalar)
{
	if (!vec)
		return ;
	vec->x *= scalar;
	vec->y *= scalar;
	vec->z *= scalar;
}

void	normalize(t_vec *v)
{
	double	len;

	len = len_vec(v);
	if (len != 0)
		scale_vec(v, 1 / len);
}
