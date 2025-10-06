/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace_color_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 16:27:04 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/10/06 17:58:36 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static t_color	shade_indirect(t_coord offset_p, t_vec normal, t_scene *scene,
	int depth, t_ray camera_ray, t_object *obj)
{
	t_vec	dir;
	t_ray	bounce;
	t_color	recursive_cl;

	dir = sum_vec(normal, random_unit_vec());
	if (dot(dir, normal) < 0.0)
		dir = neg_vec(dir);
	dir = normalized(dir);
	bounce = set_ray(offset_p, dir);
	recursive_cl = trace_color(bounce, camera_ray, scene, depth - 1);
	return (col_scale(recursive_cl, obj->material.albedo));
}

/* Computes the color recursively for a lmbertian surface*/
t_color	compute_color_lamb(t_ray ray, t_ray camera_ray, t_scene *scene, int depth)
{
	t_object	*obj;
	double		t;
	t_coord		hit_point;
	t_vec		normal;
	t_coord		offset_p;

	if (depth <= 0)
		return (color(0.0, 0.0, 0.0));
	if (!find_closest_hit(ray, scene, &obj, &t))
		return (calc_background_color(ray));
	hit_point = ray_at(ray, t);
	normal = get_normal(obj, hit_point);
	offset_p = sum_vec(hit_point, scaled(normal, EPSILON));
	return (col_sum(shade_indirect(offset_p, normal, scene, depth, camera_ray, obj),
			calc_obj_color(obj, scene, camera_ray, t)));
}

t_color	compute_color_metal(t_ray ray, t_ray camera_ray, t_scene *scene, int depth)
{

}

t_vec	get_scattered_lamb();

t_vec	get_scattered_metal();

t_color	trace_color(t_ray ray, t_ray camera_ray, t_scene *scene, int depth)
{
	t_object	*obj;
	double		t;

	if (!find_closest_hit(ray, scene, &obj, &t))
		return (calc_background_color(ray));
	if (obj->material.type == LAMBERTIAN)
		return (compute_color_lamb(ray, camera_ray, scene, depth));
	if (obj->material.type == DEFAULT)
		return (calc_obj_color(obj, scene, ray, t));
	else
		return (calc_obj_color(obj, scene, ray, t));	
}

t_vec	reflected(t_vec v, t_vec normal)
{
	return (sub_vec(v, scaled(normal, 2.0 * dot(v, normal))));
}
