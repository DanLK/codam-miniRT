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
	t_coord	hit_point;
	t_vec	v; //vector from center to hitpoint
	double	proj;//projection onto axis

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

/*************************************************************
 * hit_dist stores the hit distances to:
 * [0] - top cap
 * [1] - bottom cap
 * [2] - walls
 *************************************************************/
bool	hit_cylinder(t_object *obj, t_ray ray, double *dist)
{
	bool	hits_tcap;
	bool	hits_bcap;
	bool	hits_wall;
	double	hit_dist[3];
	double	nearest;

	hit_dist[0] = DBL_MAX;
	hit_dist[1] = DBL_MAX;
	hit_dist[2] = DBL_MAX;
	nearest = DBL_MAX;
	hits_tcap = hit_cap(obj, ray, &hit_dist[0], 't');
	hits_bcap = hit_cap(obj, ray, &hit_dist[1], 'b');
	hits_wall = hit_wall(obj, ray, &hit_dist[2]);
	if (hits_tcap && hit_dist[0] > EPSILON)
		nearest = fmin(nearest, hit_dist[0]);
	if (hits_bcap && hit_dist[1] > EPSILON)
		nearest = fmin(nearest, hit_dist[1]);
	if (hits_wall && hit_dist[2] > EPSILON)
		nearest = fmin(nearest, hit_dist[2]);
	if (nearest < DBL_MAX)
	{
		*dist = nearest;
		return (true);
	}
	return (false);
}
