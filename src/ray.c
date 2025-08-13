/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 16:03:41 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/13 15:23:02 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_cord	*ray_at(t_ray *ray, double t)
{
	t_cord	*pos;
	t_cord	*origin;
	t_vec	*dir;

	if (!ray)
		return (NULL);
	origin = init_vec(ray->origin->x, ray->origin->y, ray->origin->z);
	if (!origin)
		return (NULL);
	dir = init_vec(ray->dir->x, ray->dir->y, ray->dir->z);
	if (!dir)
		return (NULL);
	scale_vec(dir, t);
	pos = sum_vec(origin, dir);
	if (!pos)
		return (NULL);
	return (free(origin), free(dir), pos);
}

// t_vec	*compute_primray(double x, double y, )