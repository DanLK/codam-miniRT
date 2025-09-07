/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_cal_checkerboard_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:23:59 by hogu              #+#    #+#             */
/*   Updated: 2025/09/05 12:24:00 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* Map a normalized 2D coordinate d[2], both in [0,1],
 * to a fixed-size checkerboard grid, and return the corresponding color.
 * 
 * Return base color if the cell index (row+col) is even, and white if odd. */
static t_color	coord_to_color(t_color obj_color, double u, double v)
{
	int	iu;
	int	iv;

	iu = (int)floor(u * CHKB_COLS);
	iv = (int)floor(v * CHKB_ROWS);
	if ((iu + iv) % 2 == 0)
		return (obj_color);
	else
		return ((t_color){255, 255, 255});
}

t_color	cal_pl_chkb(t_object *obj, t_coord hit_p)
{
	t_vec	v;
	t_coord	local;

	v = sub_vec(hit_p, obj->center);
	get_local_coord(&obj->pl.basis, &local, v);
	if ((int)(floor(local.x) + floor(local.y)) % 2 == 0)
		return (obj->color);
	else
		return ((t_color){255, 255, 255});
}

t_color	cal_sp_chkb(t_object *obj, t_coord hit_p)
{
	t_vec	normal;
	double	longtitude;
	double	latitude;
	double	u;
	double	v;

	normal = get_sphere_normal(obj, hit_p);
	longtitude = atan2(normal.z, normal.x);
	u = (longtitude + M_PI) / (2.0 * M_PI);
	latitude = acos(normal.y);
	v = latitude / M_PI;
	return (coord_to_color(obj->color, u, v));
}

t_color	cal_cy_chkb_cap(t_object *obj, t_vec v)
{
	t_coord	local;

	get_local_coord(&obj->cy.basis, &local, v);
	if ((int)(floor(local.x) + floor(local.y)) % 2 == 0)
		return (obj->color);
	else
		return ((t_color){255, 255, 255});
}

t_color	cal_cy_chkb_curved_surface(t_object *obj, t_vec v, double proj)
{
	t_coord	local;
	t_vec	radial;
	double	longtitude;
	double	m;
	double	n;

	m = (proj + obj->cy.height / 2.0) / obj->cy.height; // map to [0,1]
	radial = sub_vec(v, scaled(obj->cy.dir, proj));
	get_local_coord(&obj->cy.basis, &local, radial);
	longtitude = atan2(local.x, local.y);
	n = (longtitude + M_PI) / (2.0 * M_PI);
	return (coord_to_color(obj->color, m, n));
}
