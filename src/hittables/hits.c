/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hits.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 14:50:48 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/26 15:37:38 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* 
The vector abc is to represent the variables a, b and c in the general
solution for a quadratic equation. abc.x = a, abc.y = b, abc.z = z
*/
bool	hit_sphere(t_object *obj, t_ray ray, double *dist)
{
	t_vec	abc;
	double	rad;
	double	discriminant;
	double	t0;
	double	t1;

	rad = obj->sp.diameter / 2.0;
	abc.x = dot(ray.dir, ray.dir);
	abc.y = -2.0 * dot(ray.dir, sum_vec(obj->center, neg_vec_new(ray.origin)));
	abc.z = dot(sum_vec(obj->center, neg_vec_new(ray.origin)),
			sum_vec(obj->center, neg_vec_new(ray.origin))) - (rad * rad);
	discriminant = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discriminant < 0)
		return (false);
	t0 = (-abc.y - sqrt(discriminant)) / (2.0 * abc.x);
	t1 = (-abc.y + sqrt(discriminant)) / (2.0 * abc.x);
	if (t0 > EPSILON)
		*dist = t0;
	else if (t1 > EPSILON)
		*dist = t1;
	else
		return (false);
	return (true);
}

bool	hit_plane(t_object *obj, t_ray ray, double *dist)
{
	t_vec	oc;
	double	denominator;
	double	numerator;

	denominator = dot(ray.dir, obj->pl.dir);
	if (fabs(denominator) < EPSILON)
		return (false);
	oc = sub_vec(obj->center, ray.origin);
	numerator = dot(oc, obj->pl.dir);
	*dist = numerator / denominator;
	if (*dist < EPSILON)
		return (false);
	return (true);
}

static bool	hit_topcap(t_object *obj, t_ray ray, double *dist)
{
	t_coord	top_cap_center;
	double	t;
	double	denom;
	t_coord	point;

	top_cap_center = sub_vec(obj->center, scaled(obj->cy.dir, obj->cy.height / 2.0));
	denom = dot(ray.dir, obj->cy.dir);
	if (fabs(denom) < EPSILON)
		return (false);
	t = dot(sub_vec(top_cap_center, ray.origin), obj->cy.dir) / denom;
	point = sum_vec(ray.origin, scaled(ray.dir, t));
	if (len_vec(sub_vec(point, top_cap_center)) > (obj->cy.diameter) / 2.0)
		return (false);
	*dist = t;
	return (true);
}

// static bool	hit_botcap(t_object *obj, t_ray ray, double *dist)
// {
// 	t_coord	bot_cap_center;

// 	bot_cap_center = sum_vec(obj->center, scaled(obj->cy.dir, obj->cy.height / 2.0));
// 	if (dot(ray.dir, neg_vec_new(obj->cy.dir)) == 0)
// }

bool	hit_cylinder(t_object *obj, t_ray ray, double *dist)
{
	return (hit_topcap(obj, ray, dist));
}

bool	hit_object(t_ray ray, t_object *obj, double *dist)
{
	if (obj->type == SPHERE)
		return (hit_sphere(obj, ray, dist));
	else if (obj->type == PLANE)
		return (hit_plane(obj, ray, dist));
	else if (obj->type == CYLINDER)
		return (hit_cylinder(obj, ray, dist));
	return (false);
}
