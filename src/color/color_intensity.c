/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_intensity.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/22 14:50:29 by hogu          #+#    #+#                 */
/*   Updated: 2025/09/26 15:03:01 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	get_sphere_normal(t_object *obj, t_coord hit_p)
{
	return (normalized(sub_vec(hit_p, obj->center)));
}

int	find_point_on_cylinder(t_object *obj, t_coord hit_p, t_vec *v, double *proj)
{
	*v = sub_vec(hit_p, obj->center);
	*proj = dot(*v, obj->cy.dir);
	if (check_equal(*proj, obj->cy.height / 2))
		return (TOP_CAP);
	if (check_equal(*proj, -obj->cy.height / 2))
		return (BOTTOM_CAP);
	else
		return (WALL);
}

static t_vec	get_cylinder_normal(t_object *obj, t_coord hit_p)
{
	int		pos;
	t_vec	v;
	double	proj;

	pos = find_point_on_cylinder(obj, hit_p, &v, &proj);
	if (pos == TOP_CAP)
		return (obj->cy.dir);
	else if (pos == BOTTOM_CAP)
		return (neg_vec(obj->cy.dir));
	else
		return (normalized(sub_vec(v, scaled(obj->cy.dir, proj))));
}

t_vec	get_normal(t_object *obj, t_coord hit_point)
{
	if (obj->type == SPHERE)
		return (get_sphere_normal(obj, hit_point));
	if (obj->type == PLANE)
		return (obj->pl.dir);
	if (obj->type == CYLINDER)
		return (get_cylinder_normal(obj, hit_point));
	else
		return (vec(0, 0, 0));
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
	intensity = fmin(1.0, fmax(0.0, dot(normal, light_dir)));
	return (intensity);
}
