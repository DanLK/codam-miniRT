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

t_vec	get_sphere_normal(t_hit_point *hp)
{
	return (normalized(sub_vec(hp->hp, hp->obj->center)));
}

int	find_point_on_cylinder(t_hit_point *hp, t_vec *v, double *proj)
{
	*v = sub_vec(hp->hp, hp->obj->center);
	*proj = dot(*v, hp->obj->cy.dir);
	if (check_equal(*proj, hp->obj->cy.height / 2))
		return (TOP_CAP);
	if (check_equal(*proj, -hp->obj->cy.height / 2))
		return (BOTTOM_CAP);
	else
		return (WALL);
}

static t_vec	get_cylinder_normal(t_hit_point *hp)
{
	int		pos;
	t_vec	v;
	double	proj;

	pos = find_point_on_cylinder(hp, &v, &proj);
	if (pos == TOP_CAP)
		return (hp->obj->cy.dir);
	else if (pos == BOTTOM_CAP)
		return (neg_vec(hp->obj->cy.dir));
	else
		return (normalized(sub_vec(v, scaled(hp->obj->cy.dir, proj))));
}

//returns an outward, normalized vector
t_vec	get_normal(t_hit_point *hp)
{
	if (hp->obj->type == SPHERE)
		return (get_sphere_normal(hp));
	if (hp->obj->type == PLANE)
		return (hp->obj->pl.dir);
	if (hp->obj->type == CYLINDER)
		return (get_cylinder_normal(hp));
	else
		return (vec(0, 0, 0));
}

/*
	logic see math_updated.txt
	Normal vectors are calculated based on object type and hit_point position.
*/
double	calc_intensity(t_hit_point *hp, t_coord light_p)
{
	t_vec	light_dir;
	double	intensity;

	light_dir = normalized(sub_vec(light_p, hp->hp));
	intensity = fmin(1.0, fmax(0.0, dot(hp->normal, light_dir)));
	return (intensity);
}
