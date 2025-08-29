/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/27 11:41:53 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/29 17:52:37 by dloustal      ########   odam.nl         */
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

static bool	in_bounds(t_object *obj, t_ray ray, double *dist, double t)
{
	double	to_center;

	to_center = dot(sum_vec(ray.origin, scaled(ray.dir, t)), obj->cy.dir);
	if (to_center <= obj->cy.height / 2.0 && to_center >= -(obj->cy.height / 2.0))
	{
		*dist = t;
		return (true);
	}
	return (false);

}	

static bool	hit_wall(t_object *obj, t_ray ray, double *dist)
{
	t_coord	p;
	t_coord	w;
	t_coord	x;
	double	disc;
	double	rad;
	double	coef[3];
	double	t0;
	double	t1;

	rad = obj->cy.diameter / 2.0;
	p = sub_vec(ray.origin, obj->center);
	w = sub_vec(p, scaled(obj->cy.dir, dot(p, obj->cy.dir)));
	x = sub_vec(ray.dir, scaled(obj->cy.dir, dot(ray.dir, obj->cy.dir)));
	coef[0] = dot(x, x);
	coef[1] = 2.0 * dot(w, x);
	coef[2] = dot(w, w) - rad * rad;
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

bool	hit_cylinder(t_object *obj, t_ray ray, double *dist)
{
	bool	hits_tcap;
	bool	hits_bcap;
	bool	hits_wall;
	double	dtcap;
	double	dbcap;
	double	dwall;

	dtcap = 0;
	dbcap = 0;
	dwall = 0;
	hits_tcap = hit_cap(obj, ray, &dtcap, 't');
	hits_bcap = hit_cap(obj, ray, &dtcap, 'b');
	hits_wall = hit_wall(obj, ray, &dwall);
	if (hits_tcap && hits_wall)
	{
		*dist = fmin(dtcap, dwall);
		return (true);
	}
	else if (hits_wall)
	{
		*dist = dwall;
		return (true);
	}

	return (false);
}