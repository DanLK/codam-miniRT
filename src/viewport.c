/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   viewport.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 16:08:18 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/14 17:16:49 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_coord	calculate_p00(t_vport vp)
{
	t_coord	p00;
	t_coord	corner;

	corner = sum_vec(vp.center, sum_vec(scaled(vp.v_up, vp.height / 2.0),
		neg_vec_new(scaled(vp.v_right, vp.width / 2.0))));
	print_vec(&corner, "corner");
	
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
	viewport->height = (double)(viewport->width * viewport->ratio);
	viewport->center = scaled(sum_vec(cam.pos, cam.dir), viewport->distance);
	viewport->v_right = normalized(cross(vec(0.0, 1.0, 0.0), cam.dir));
	viewport->v_up = normalized(cross(viewport->v_right, cam.dir)); //Not sure if it has to point up or down
	viewport->delta_x = scaled(viewport->v_right, 1.0 / WIDTH);
	viewport->delta_y = scaled(viewport->v_up, 1.0 / HEIGHT);
	print_vec(&viewport->delta_x, "delta_x");
	print_vec(&viewport->delta_y, "delta_y");
	viewport->p_00 = calculate_p00(*viewport);
}


