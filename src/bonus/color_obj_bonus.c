/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 17:21:38 by hogu              #+#    #+#             */
/*   Updated: 2025/09/01 17:21:39 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static t_color	get_chkb_color(t_object *obj, t_coord hit_p)
{
	int		cy_pos;
	t_vec	v;
	double	proj;

	if (obj->type == SPHERE)
		return (cal_sp_chkb(obj, hit_p));
	else if (obj->type == PLANE)
	{
		if (!obj->pl.basis.ready)
			set_local_basis(obj->pl.dir, &obj->pl.basis);
		return (cal_pl_chkb(obj, hit_p));
	}
	else
	{
		cy_pos = find_point_on_cylinder(obj, hit_p, &v, &proj);
		if (!obj->cy.basis.ready)
			set_local_basis(obj->cy.dir, &obj->cy.basis);
		if (cy_pos == CURVED_SURFACE)
			return (cal_cy_chkb_curved_surface(obj, v, proj));
		else
			return (cal_cy_chkb_cap(obj, v));
	}
}

t_color	calc_obj_color(t_object *obj, t_scene *scn, t_ray ray, double t)
{
	t_coord	hit_point;
	t_color	obj_amb;
	t_color	obj_dif;
	bool	in_shadow;

	in_shadow = true;
	hit_point = ray_at(ray, t);
	if (obj->is_chkb)
		obj->show_color = get_chkb_color(obj, hit_point);
	else
		obj->show_color = obj->color;
	obj_amb = calc_obj_solo(obj->show_color, scn->ambient.color, scn->ambient.ratio, 1);
	obj_dif = cal_diffuse(scn, hit_point, obj, &in_shadow);
	if (in_shadow)
		return (obj_amb);
	else
		return (sum_color(obj_amb, obj_dif));
}
