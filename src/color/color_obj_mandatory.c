/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_obj_mandatory.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 14:28:16 by dloustal      #+#    #+#                 */
/*   Updated: 2025/09/26 14:52:51 by dloustal      ########   odam.nl         */
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
	bool	in_shadow;

	in_shadow = true;
	hit_point = ray_at(ray, t);
	obj->show_color = obj->color;
	obj_amb = calc_obj_solo(obj->show_color, scn->ambient.color,
			scn->ambient.ratio, 1.0);
	obj_dif = cal_diffuse(scn, hit_point, obj, &in_shadow);
	if (in_shadow)
		return (obj_amb);
	else
		return (sum_color(obj_amb, obj_dif));
}
