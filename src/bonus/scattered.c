/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scattered.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/10 15:31:09 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/10/10 15:56:12 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

bool	get_scattered_ray(t_ray ray, t_hit_point hp, t_ray *scattered, double *attenuation)
{
	if (hp.obj->material.type == LAMBERTIAN)
		return (get_scattered_lmb(ray, hp, scattered, attenuation));
	if (hp.obj->material.type == METAL)
		return (get_scattered_metal(ray, hp, scattered, attenuation));
	if (hp.obj->material.type == DEFAULT)
		{
			*scattered = ray;
			*attenuation = 0.0;
		}
	return (true);
}

bool	get_scattered_lmb(t_ray ray, t_hit_point hp, t_ray *scatt, double *att)
{
	t_vec	dir;
	t_coord	offset_p;

	(void)ray;
	dir = sum_vec(hp.normal, random_unit_vec());
	if (dot(dir, hp.normal) < 0.0)
		dir = neg_vec(dir);
	dir = normalized(dir);
	offset_p = sum_vec(hp.hp, scaled(hp.normal, EPSILON));
	*scatt = set_ray(offset_p, dir);
	*att = hp.obj->material.albedo;
	return (true);
}

static t_vec	reflected(t_vec v, t_vec normal)
{
	return (sub_vec(v, scaled(normal, 2.0 * dot(v, normal))));
}

bool	get_scattered_metal(t_ray ray, t_hit_point hp, t_ray *scatt, double *att)
{
	t_vec ref_dir;

	ref_dir = reflected(ray.dir, hp.normal);
	*scatt = set_ray(hp.hp, ref_dir);
	*att = hp.obj->material.albedo;
	return (true);
}