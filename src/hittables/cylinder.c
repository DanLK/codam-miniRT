/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 11:41:53 by dloustal      #+#    #+#                 */
/*   Updated: 2025/09/03 14:51:33 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*cap = 't' is for top cap and cap = 'b' is for bottom cap */
static void	find_cap_center_and_normal(t_object *obj, char cap,
		t_coord *cap_center, t_coord *normal)
{
	if (cap == 't')
	{
		*cap_center = sum_vec(obj->center, scaled(obj->cy.dir,
					obj->cy.height / 2.0));
		*normal = obj->cy.dir;
	}
	else
	{
		*cap_center = sub_vec(obj->center, scaled(obj->cy.dir,
					obj->cy.height / 2.0));
		*normal = neg_vec(obj->cy.dir);
	}
}

bool	hit_cap(t_object *obj, t_ray ray, double *dist, char cap)
{
	t_coord	cap_center;
	t_coord	normal;
	double	denom;
	double	t;
	t_coord	point;

	find_cap_center_and_normal(obj, cap, &cap_center, &normal);
	denom = dot(ray.dir, normal);
	if (fabs(denom) < EPSILON)
		return (false);
	t = dot(sub_vec(cap_center, ray.origin), normal) / denom;
	if (t <= EPSILON)
		return (false);
	point = sum_vec(ray.origin, scaled(ray.dir, t));
	if (len_vec(sub_vec(point, cap_center)) > (obj->cy.diameter) / 2.0)
		return (false);
	*dist = t;
	return (true);
}

/*v = vector from center to hitpoint; proj = projection onto axis*/
static bool	in_bounds(t_object *obj, t_ray ray, double *dist, double t)
{
	t_coord	hit_point;
	t_vec	v;
	double	proj;

	hit_point = sum_vec(ray.origin, scaled(ray.dir, t));
	v = sub_vec(hit_point, obj->center);
	proj = dot(v, obj->cy.dir);
	if (proj <= obj->cy.height / 2.0 && proj >= -(obj->cy.height / 2.0))
	{
		*dist = t;
		return (true);
	}
	return (false);
}

bool	quadratic_check(double coef[3], t_object *obj, t_ray ray, double *dist)
{
	double	disc;
	double	t0;
	double	t1;

	disc = coef[1] * coef[1] - (4.0 * coef[0] * coef[2]);
	if (disc < 0)
		return (false);
	t0 = (-coef[1] - sqrt(disc)) / (2.0 * coef[0]);
	t1 = (-coef[1] + sqrt(disc)) / (2.0 * coef[0]);
	if (t0 > EPSILON && in_bounds(obj, ray, dist, t0))
		return (true);
	else if (t1 > EPSILON && in_bounds(obj, ray, dist, t1))
		return (true);
	else
		return (false);
}

bool	hit_wall(t_object *obj, t_ray ray, double *dist)
{
	t_coord	p;
	t_coord	w;
	t_coord	x;
	double	rad;
	double	coef[3];

	rad = obj->cy.diameter / 2.0;
	p = sub_vec(ray.origin, obj->center);
	w = reject(p, obj->cy.dir);
	x = reject(ray.dir, obj->cy.dir);
	coef[0] = dot(x, x);
	coef[1] = 2.0 * dot(w, x);
	coef[2] = dot(w, w) - rad * rad;
	return (quadratic_check(coef, obj, ray, dist));
}
