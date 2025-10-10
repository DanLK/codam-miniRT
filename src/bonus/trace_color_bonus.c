/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace_color_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 16:27:04 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/10/10 16:39:31 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

// static t_color	shade_indirect(t_coord offset_p, t_vec normal, t_scene *scene,
// 	int depth, t_ray camera_ray, t_object *obj)
// {
// 	t_vec	dir;
// 	t_ray	bounce;
// 	t_color	recursive_cl;

// 	dir = sum_vec(normal, random_unit_vec());
// 	if (dot(dir, normal) < 0.0)
// 		dir = neg_vec(dir);
// 	dir = normalized(dir);
// 	bounce = set_ray(offset_p, dir);
// 	recursive_cl = trace_color(bounce, camera_ray, scene, depth - 1);
// 	return (col_scale(recursive_cl, obj->material.albedo));
// }

// /* Computes the color recursively for a lmbertian surface*/
// t_color	compute_color_lamb(t_ray ray, t_ray camera_ray, t_scene *scene, int depth)
// {
// 	// t_object	*obj;
// 	// double		t;
// 	// t_coord		hit_point;
// 	// t_vec		normal;
// 	t_coord		offset_p;
// 	t_hit_point	hp;

// 	if (depth <= 0)
// 		return (color(0.0, 0.0, 0.0));
// 	if (!find_closest_hit(ray, scene, &hp))
// 		return (calc_background_color(ray));
// 	// hit_point = ray_at(ray, t);
// 	// normal = get_normal(obj, hit_point);
// 	offset_p = sum_vec(hp.hp, scaled(hp.normal, EPSILON));
// 	return (col_sum(shade_indirect(offset_p, hp.normal, scene, depth, camera_ray, hp.obj),
// 			calc_obj_color(hp.obj, scene, camera_ray, hp.t)));
// }

t_color	trace_color(t_ray ray, t_ray camera_ray, t_scene *scene, int depth)
{
	t_hit_point	hp;
	t_ray		scattered;
	double		attenuation;

	if (depth <= 0)
		return (color(0.0, 0.0, 0.0));
	if (!find_closest_hit(ray, scene, &hp))
		return (calc_background_color(ray));
	if (get_scattered_ray(ray, hp, &scattered, &attenuation))
		return (col_sum(col_scale(trace_color(scattered, camera_ray, scene, depth - 1),
				attenuation), calc_obj_color(hp.obj, scene, camera_ray, hp.t)));
	return color(0.0, 0.0, 0.0);
}

// t_color	trace_color(t_ray ray, t_ray camera_ray, t_scene *scene, int depth)
// {
// 	// t_object	*obj;
// 	// double		t;
// 	t_hit_point	hp;

// 	if (!find_closest_hit(ray, scene, &hp))
// 		return (calc_background_color(ray));
// 	if (hp.obj->material.type == LAMBERTIAN)
// 		return (compute_color_lamb(ray, camera_ray, scene, depth));
// 	if (hp.obj->material.type == DEFAULT)
// 		return (calc_obj_color(hp.obj, scene, ray, hp.t));
// 	else
// 		return (calc_obj_color(hp.obj, scene, ray, hp.t));	
// }
