/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 16:30:45 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/07 16:58:47 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

double	len_vec(t_vec *vec)
{
	double	len;
	if (!vec)
		return ;
	len = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	return (len);
}

double	dot(t_vec *u, t_vec *v)
{
	double	dot;

	if (!u || !v)
		return (-1); //Not really sure what to return here, maybe epsilon or infinity
	dot = u->x * v->x + u->y * v->y + u->z * v->z;
	return (dot);

}
