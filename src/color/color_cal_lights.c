/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_cal_lights.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/10 11:52:45 by hogu          #+#    #+#                 */
/*   Updated: 2025/09/26 14:41:08 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
calculate object lighting effect under one light source. 
	for ambient light, 'intensity' = 1
	for point light, use calculated diffuse_intensity from calc_intensity()
*/

t_color	calc_obj_solo(t_color obj, t_color light, double ratio, double intens)
{
	t_color	ret;

	ret.r = obj.r * light.r * ratio * intens;
	ret.g = obj.g * light.g * ratio * intens;
	ret.b = obj.b * light.b * ratio * intens;
	return (ret);
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

t_color	cal_diffuse(t_scene *scn, t_coord hit_p, t_object *obj, bool *in_shadow)
{
	t_color	sum;
	t_color	single;
	t_light	*cur;
	double	intensity;

	sum = (t_color){0, 0, 0};
	cur = scn->light;
	while (cur)
	{
		if (!is_in_shadow(hit_p, scn->objects, cur->pos))
		{
			*in_shadow = false;
			intensity = calc_intensity(hit_p, obj, cur->pos);
			single = calc_obj_solo(obj->show_color, cur->color, cur->ratio,
					intensity);
			sum = col_sum(sum, single);
		}
		cur = cur->next;
	}
	return (sum);
}
