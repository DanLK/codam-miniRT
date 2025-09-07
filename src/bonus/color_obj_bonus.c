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

#include "miniRT.h"

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
	t_color	obj_cl;
	t_color	obj_amb;
	t_color	obj_dif;
	double	intens;

	hit_point = ray_at(ray, t);
	if (obj->is_chkb)
		obj_cl = get_chkb_color(obj, hit_point);
	else
		obj_cl = obj->color;
	obj_amb = calc_obj_solo(obj_cl, scn->ambient.color,
			scn->ambient.ratio, 1);
	if (is_in_shadow(hit_point, scn->objects, scn->light.pos))
		return (obj_amb);
	intens = calc_intensity(hit_point, obj, scn->light.pos);
	obj_dif = calc_obj_solo(obj_cl, scn->light.color, scn->light.ratio,
			intens);
	return (sum_color(obj_amb, obj_dif));
}
