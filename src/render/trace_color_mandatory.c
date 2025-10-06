/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   trace_color_mandatory.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/06 16:40:24 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/10/06 16:46:09 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	trace_color(t_ray ray, t_ray camera_ray, t_scene *scene, int depth)
{
	t_object	*obj;
	double		t_min;

	(void)camera_ray;
	(void)depth;
	if (!find_closest_hit(ray, scene, &obj, &t_min))
		return (calc_background_color(ray));
	return(calc_obj_color(obj, scene, ray, t_min));
}
