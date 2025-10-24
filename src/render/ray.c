/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 16:03:41 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/21 16:12:58 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	ray_at(t_ray ray, double t)
{
	t_coord	pos;

	pos = sum_vec(ray.origin, scaled(ray.dir, t));
	return (pos);
}

t_ray	set_ray(t_coord start, t_vec ray_dir)
{
	t_ray	ray;

	ray.dir = normalized(ray_dir);
	ray.origin = start;
	return (ray);
}
