/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   viewport.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 16:08:18 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/14 12:29:36 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	make_vport(t_camera cam, t_vport *viewport)
{	
	double	angle_rad;
	t_vec	vx;
	t_vec	vy;
	t_vec	delta_x;
	t_vec	delta_y;

	angle_rad = M_PI * cam.fov / 180.0 / 2.0;
	viewport->width = atanh(angle_rad) * 2;
	viewport->height = (double)(viewport->width * (HEIGHT / WIDTH));
	vx.x = cam.pos.x + viewport->width;
	vx.y = cam.pos.y;
	vx.z = cam.pos.z;
	viewport->vx = vx;
	vy.x = cam.pos.x;
	vy.y = cam.pos.y - viewport->height;
	vy.z = cam.pos.z;
	viewport->vy = vy;
	delta_x = viewport->vx;
	delta_y = viewport->vy;
	scale_vec(&delta_x, 1 / WIDTH);
	scale_vec(&delta_y, 1 / HEIGHT);
	viewport->delta_x = delta_x;
	viewport->delta_y = delta_y;
}


