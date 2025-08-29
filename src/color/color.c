/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 14:28:16 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/27 12:38:13 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	is_in_shadow(t_coord hit_p, t_object *obj, t_coord light_p)
{
	t_vec	shadow_dir;
	t_ray	shadow_ray;
	double	hit_obj_t;
	double	hit_light_t;

	shadow_dir = sub_vec(light_p, hit_p);
	hit_light_t = len_vec(shadow_dir);
	shadow_ray = set_ray(hit_p, shadow_dir);
	while (obj)
	{
		if (hit_object(shadow_ray, obj, &hit_obj_t) && hit_obj_t > EPSILON
			&& hit_obj_t < hit_light_t)
			return (true);
		obj = obj->next;
	}
	return (false);
}

/*
calculate object lighting effect under one light source. 
	for ambient light, 'intensity' = 1
	for point light, use calculated diffuse_intensity from calc_intensity()
*/
static t_color	calc_obj_solo(t_color obj, t_color light, double ratio,
								double intens)
{
	t_color	ret;

	ret.r = obj.r * light.r / 255.0 * ratio * intens;
	ret.g = obj.g * light.g / 255.0 * ratio * intens;
	ret.b = obj.b * light.b / 255.0 * ratio * intens;
	return (ret);
}

/*	
calculate object color for hit_points.
	- obj->color: object's original color;
	- obj_amb: effect under ambient light only;
	- obj_dif: effect under point light only;	
*/
t_color	calc_obj_color(t_object *obj, t_scene *scn, t_ray ray, double t)
{
	t_coord	hit_point;
	t_color	obj_amb;
	t_color	obj_dif;
	double	intens;

	hit_point = ray_at(ray, t);
	obj_amb = calc_obj_solo(obj->color, scn->ambient.color,
			scn->ambient.ratio, 1);
	if (is_in_shadow(hit_point, scn->objects, scn->light.pos))
		return (obj_amb);
	intens = calc_intensity(hit_point, obj, scn->light.pos);
	obj_dif = calc_obj_solo(obj->color, scn->light.color, scn->light.ratio,
			intens);
	return (sum_color(obj_amb, obj_dif));
}

t_color	calc_background_color(t_ray ray)
{
	t_color	color;
	t_vec	unit_dir;
	double	a;

	unit_dir = normalized(ray.dir);
	a = 0.5 * (unit_dir.y + 1.0);
	color.r = (1 - a) * 255 + a * 25;
	color.g = (1 - a) * 255 + a * 25;
	color.b = (1 - a) * 255 + a * 112;
	return (color);
}

// // //testing code: shows object_color as it is
// t_color	calc_obj_color(t_object *obj, t_scene *scn, t_ray ray, double t)
// {
// 	(void) t;
// 	(void) scn;
// 	(void) ray;

// 	return (obj->color);
// }