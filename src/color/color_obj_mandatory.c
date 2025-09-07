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

// // //testing code: shows object_color as it is
// t_color	calc_obj_color(t_object *obj, t_scene *scn, t_ray ray, double t)
// {
// 	(void) t;
// 	(void) scn;
// 	(void) ray;

// 	return (obj->color);
// }