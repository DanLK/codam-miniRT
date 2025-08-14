/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 16:03:41 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/14 16:31:44 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	ray_at(t_ray ray, double t)
{
	t_coord	pos;

	pos = sum_vec(ray.origin, scaled(ray.dir, t));
	return (pos);
}

t_vec	prim_ray_dir(t_camera cam, t_coord pixel)
{
	t_vec	prim_ray_dir;

	prim_ray_dir.x = pixel.x - cam.pos.x;
	prim_ray_dir.y = pixel.y - cam.pos.y;
	prim_ray_dir.z = pixel.z - cam.pos.z;
	return (prim_ray_dir);
}

t_ray	set_ray(t_camera cam, t_vec prim_ray_dir)
{
	t_ray	ray;

	ray.dir = prim_ray_dir;
	ray.origin = cam.pos;
	return (ray);
}