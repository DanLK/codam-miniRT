/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   color_utils.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/22 15:41:46 by hogu           #+#    #+#                */
/*   Updated: 2025/08/22 15:41:47 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/* sum the effect of 2 colors and make sure it is still in valid range*/
t_color	sum_color(t_color cl1, t_color cl2)
{
	t_color	ret;

	ret.r = cl1.r + cl2.r;
	ret.g = cl1.g + cl2.g;
	ret.b = cl1.b + cl2.b;
	ret.r = fmin(ret.r, 255);
	ret.g = fmin(ret.g, 255);
	ret.b = fmin(ret.b, 255);
	return (ret);
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

/*
calculate object lighting effect under one light source. 
	for ambient light, 'intensity' = 1
	for point light, use calculated diffuse_intensity from calc_intensity()
*/
t_color	calc_obj_solo(t_color obj, t_color light, double ratio,
								double intens)
{
	t_color	ret;

	ret.r = obj.r * light.r / 255.0 * ratio * intens;
	ret.g = obj.g * light.g / 255.0 * ratio * intens;
	ret.b = obj.b * light.b / 255.0 * ratio * intens;
	return (ret);
}

bool	is_in_shadow(t_coord hit_p, t_object *obj, t_coord light_p)
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
