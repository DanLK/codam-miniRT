/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   viewport.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 16:08:18 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/27 12:12:07 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_coord	calculate_p00(t_vport vp)
{
	t_coord	p00;
	t_coord	corner;

	corner = sum_vec(vp.center, sum_vec(neg_vec_new(scaled(vp.v_down,
						vp.height / 2.0)),
				neg_vec_new(scaled(vp.v_right, vp.width / 2.0))));
	print_vec_name(&corner, "corner");
	p00.x = corner.x + 0.5 * (vp.delta_x.x + vp.delta_y.x);
	p00.y = corner.y + 0.5 * (vp.delta_x.y + vp.delta_y.y);
	p00.z = corner.z + 0.5 * (vp.delta_x.z + vp.delta_y.z);
	return (p00);
}

void	make_vport(t_camera cam, t_vport *viewport)
{
	double	angle_rad;

	angle_rad = cam.fov * (M_PI / 180.0);
	viewport->distance = 1.0;
	viewport->ratio = (double)WIDTH / HEIGHT;
	viewport->width = tan(angle_rad / 2) * 2.0 * viewport->distance;
	viewport->height = (double)(viewport->width / viewport->ratio);
	viewport->center = sum_vec(cam.pos, scaled(normalized(cam.dir),
				viewport->distance));
	viewport->v_right = normalized(cross(vec(0.0, 1.0, 0.0), cam.dir));
	viewport->v_down = normalized(cross(viewport->v_right, cam.dir));
	viewport->delta_x = scaled(viewport->v_right, viewport->width / WIDTH);
	viewport->delta_y = scaled(viewport->v_down, viewport->height / HEIGHT);
	print_vec_name(&viewport->delta_x, "delta_x");
	print_vec_name(&viewport->delta_y, "delta_y");
	viewport->p_00 = calculate_p00(*viewport);
}
