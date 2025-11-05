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

static t_color	get_chkb_color(t_hit_point *hp)
{
	int		cy_pos;
	t_vec	v;
	double	proj;

	if (hp->obj->type == SPHERE)
		return (cal_sp_chkb(hp));
	else if (hp->obj->type == PLANE)
	{
		if (!hp->obj->pl.basis.ready)
			set_local_basis(hp->obj->pl.dir, &hp->obj->pl.basis);
		return (cal_pl_chkb(hp));
	}
	else
	{
		cy_pos = find_point_on_cylinder(hp, &v, &proj);
		if (!hp->obj->cy.basis.ready)
			set_local_basis(hp->obj->cy.dir, &hp->obj->cy.basis);
		if (cy_pos == WALL)
			return (cal_cy_chkb_curved_surface(hp->obj, v, proj));
		else
			return (cal_cy_chkb_cap(hp->obj, v));
	}
}

t_color	calc_obj_color(t_hit_point *hp, t_scene *scene)
{
	t_color	obj_amb;
	t_color	obj_dif;
	bool	in_shadow;

	in_shadow = true;
	if (hp->obj->is_chkb)
		hp->obj->show_color = get_chkb_color(hp);
	else
		hp->obj->show_color = hp->obj->color;
	obj_amb = calc_obj_solo(hp->obj->show_color, scene->ambient.color,
			scene->ambient.ratio, 1);
	obj_dif = cal_diffuse(scene, hp, &in_shadow);
	if (in_shadow)
		return (obj_amb);
	else
		return (col_sum(obj_amb, obj_dif));
}
