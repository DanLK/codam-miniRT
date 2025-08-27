/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hits.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 14:50:48 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/27 11:58:17 by dloustal      ########   odam.nl         */
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
	abc.y = -2.0 * dot(ray.dir, sub_vec(obj->center, ray.origin));
	abc.z = dot(sub_vec(obj->center, ray.origin),
			sub_vec(obj->center, ray.origin)) - (rad * rad);
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
