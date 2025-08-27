/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 11:41:53 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/27 12:55:16 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**********************************************************************
 * cap = 't' is for top cap and cap = 'b' is for bottom cap
 **********************************************************************/
static bool	hit_cap(t_object *obj, t_ray ray, double *dist, char cap)
{
	t_coord	cap_center;
	t_coord	normal;
	double	denom;
	double	t;
	t_coord	point;

	if (cap == 't')
	{
		cap_center = sum_vec(obj->center, scaled(obj->cy.dir, obj->cy.height / 2.0));
		normal = obj->cy.dir;
	}
	else // Assuming that we are only going to call the function with either t or b
	{
		cap_center = sub_vec(obj->center, scaled(obj->cy.dir, obj->cy.height / 2.0));
		normal = neg_vec_new(obj->cy.dir);
	}
	denom = dot(ray.dir, normal);
	if (fabs(denom) < EPSILON)
		return (false);
	t = dot(sub_vec(cap_center, ray.origin), normal) / denom;
	if (t < 0)
		return (false);
	point = sum_vec(ray.origin, scaled(ray.dir, t));
	if (len_vec(sub_vec(point, cap_center)) > (obj->cy.diameter) / 2.0)
		return (false);
	*dist = t;
	return (true);
}

bool	hit_cylinder(t_object *obj, t_ray ray, double *dist)
{
	return (hit_cap(obj, ray, dist, 'b'));
}