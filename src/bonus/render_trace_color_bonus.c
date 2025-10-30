/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace_color_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 16:27:04 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/10/22 16:57:22 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_color	trace_color(t_ray ray, t_ray camera_ray, t_scene *scene, int depth)
{
	t_hit_point	hp;
	t_color		direct;
	t_color		indirect;
	t_ray		scattered;
	t_color		attenuation;

	if (depth <= 0)
		return (color(0.0, 0.0, 0.0));
	if (!find_closest_hit(ray, scene, &hp))
		return (calc_background_color(ray));
	direct = calc_obj_color(&hp, scene);
	if (!get_scattered_ray(ray, hp, &scattered, &attenuation))
		return (direct);
	indirect = trace_color(scattered, camera_ray, scene, depth - 1);
	return (col_sum(col_scale(direct, 0.2), col_mul(attenuation, indirect)));
}
