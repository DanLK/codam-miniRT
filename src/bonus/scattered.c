/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scattered.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/10 15:31:09 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/10/22 16:55:44 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

bool	get_scattered_ray(t_ray ray, t_hit_point hp, t_ray *scattered, t_color *attenuation)
{
	if (hp.obj->material.type == LAMBERTIAN)
		return (get_scattered_lmb(ray, hp, scattered, attenuation));
	if (hp.obj->material.type == METAL)
		return (get_scattered_metal(ray, hp, scattered, attenuation));
	if (hp.obj->material.type == DEFAULT)
		{
			*scattered = ray;
			*attenuation = color(0.0, 0.0, 0.0);
		}
	return (true);
}

static bool	near_zero(t_vec vec)
{
	return (vec.x <= EPSILON && vec.y <= EPSILON && vec.z <= EPSILON);
}

bool	get_scattered_lmb(t_ray ray, t_hit_point hp, t_ray *scatt, t_color *att)
{
	t_vec	dir;
	t_coord	offset_p;

	(void)ray;
	dir = sum_vec(hp.normal, random_unit_vec());
	if (dot(dir, hp.normal) <= 0.0)
		dir = neg_vec(dir);
	// 	return (false);
	if (near_zero(dir))
		dir = hp.normal;
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

bool	get_scattered_metal(t_ray ray, t_hit_point hp, t_ray *scatt, t_color *att)
{
	t_vec 	ref_dir;
	t_vec	normal;
	t_coord	offset;

	if (dot(ray.dir, hp.normal) <= 0)
		normal = neg_vec(hp.normal);
	else
		normal = hp.normal;
	ref_dir = reflected(normalized(ray.dir), hp.normal);
	// if (dot(ref_dir, hp.normal) <= 0)
    //     ref_dir = neg_vec(ref_dir);
	offset = sum_vec(hp.hp, scaled(hp.normal, EPSILON));
	*scatt = set_ray(offset, ref_dir);
	*att = hp.obj->material.albedo;
	return (true);
}