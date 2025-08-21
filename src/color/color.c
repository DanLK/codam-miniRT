/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 14:28:16 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/19 12:07:19 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

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

t_color	get_object_color(t_object *obj, t_scene *scene, t_ray ray, double t)
{
	t_coord	hit_point;

	hit_point = ray_at(ray, t);
	if (is_in_shadow(hit_point, scene->objects, scene->light.pos))
		return (shadow_color());
	else
		return (none_shadow_color());
}


t_color get_background_color()
{
	unit_dir = normalized(ray.dir);
	a = 0.5 * (unit_dir.y + 1.0);
	// a = (unit_dir.y + 0.75) / 1.5;
	color.r = (1 - a) * 255 + a * 25;
	color.g = (1 - a) * 255 + a * 25;
	color.b = (1 - a) * 255 + a * 112;
}
