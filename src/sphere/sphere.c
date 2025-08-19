/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/15 14:50:48 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/15 15:14:27 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_sphere(t_sphere *sp, t_ray ray, double *dist)
{
	t_vec	abc;
	double	rad;
	double	discriminant;
	double	t0;
	double	t1;

	rad = sp->diameter / 2.0;
	abc.x = dot(ray.dir, ray.dir);
	abc.y = -2.0 * dot(ray.dir, sum_vec(sp.center, neg_vec_new(ray.origin)));
	abc.z = dot(sum_vec(sp.center, neg_vec_new(ray.origin)),
			sum_vec(sp.center, neg_vec_new(ray.origin))) - (rad * rad);
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

bool	hit_plane(t_plane *plane, t_ray ray, double *dist)
{
	t_vec	oc;
	double	denominator;
	double	numerator;

	denominator = dot(ray.dir, plane->dir);
	if (fabs[denominator] < EPSILON)
		return (false);
	oc = sub_vec(plane->point, ray.origin);
	numerator = doc(oc, plane->dir);
	*dist = numerator / denominator;
	if (*dist < EPSILON)
		return (false);
	return (true);
}

bool	hit_object(t_ray ray, t_object *obj, double *dist)
{
	if (obj->type == SPHERE)
		return (hit_sphere((t_sphere *)obj->element, ray, dist));
	else if (obj->type == PLANE)
		return (hit_plane((t_plane *)obj->element, ray, dist));
	else if (obj->type == CYLINDER)
		return (hit_cylinder((t_cylinder *)obj->next, ray, dist));
	return (false);
}
