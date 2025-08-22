/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   color_get_intensity.c                               :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/22 14:50:29 by hogu           #+#    #+#                */
/*   Updated: 2025/08/22 14:50:30 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	get_sphere_normal(t_sphere *sp, t_coord hit_p)
{
	return (normalized(sub_vec(hit_p, sp->center)));
}

static t_vec	get_plane_normal(t_plane *pl, t_coord hit_p)
{
	(void) hit_p;
	return (pl->dir);
}

static t_vec	get_cylinder_normal(t_cylinder *cy, t_coord hit_p)
{
	
}

static t_vec	get_normal(t_object *obj, t_coord hit_point)
{
	if (obj->type == SPHERE)
		return (get_sphere_normal((t_sphere *)obj->element, hit_point));
	if (obj->type == PLANE)
		return (get_plane_normal((t_sphere *)obj->element, hit_point));
	if (obj->type == CYLINDER)
		return (get_cylinder_normal((t_sphere *)obj->element, hit_point));
	else
		return (vec(0, 0, 0)); //fallback
}

/*
	logic see math_updated.txt
	Normal vectors are calculated based on object type and hit_point position.
*/
double	calc_intensity(t_coord hit_p, t_object *obj, t_coord light_p)
{
	t_vec	light_dir;
	t_vec	normal;
	double	intensity;

	light_dir = normalized(sub_vec(light_p, hit_p));
	normal = get_normal(obj, hit_p);
	intensity = fmax(0.0, dot(normal, light_dir));
	return (intensity);
}
