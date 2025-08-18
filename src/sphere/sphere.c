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

bool	hit_sphere(t_sphere sphere, t_ray ray)
{
	double	a;
	double	b;
	double	c;
	double	rad;
	double	discriminant;

	rad = sphere.diameter / 2.0;
	a = dot(ray.dir, ray.dir);
	b = -2.0 * dot(ray.dir, sum_vec(sphere.center, neg_vec_new(ray.origin)));
	c = dot(sum_vec(sphere.center, neg_vec_new(ray.origin)),
		sum_vec(sphere.center, neg_vec_new(ray.origin))) - (rad * rad);
	discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}