/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   color_local_basis_bonus.c                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/09/04 12:03:48 by hogu           #+#    #+#                */
/*   Updated: 2025/09/04 12:03:49 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_local_basis(t_vec dir, t_basis *basis)
{
	t_vec	world_up;

	world_up = vec(0.0, 1.0, 0.0);
	basis->x_axis = normalized(cross(dir, world_up));
	if (len_vec(basis->x_axis) < EPSILON) // in case if obj->pl.dir is parallel to world_up
	{
		world_up = vec(1.0, 0.0, 0.0); // use (1, 0, 0) instead
		basis->x_axis = normalized(cross(dir, world_up));
	}
	basis->y_axis = cross(dir, basis->x_axis);
	basis->ready = true;
}

void	get_local_coord(t_basis *basis, t_coord *local, t_vec v)
{
	local->x = dot(v, basis->x_axis);
	local->y = dot(v, basis->y_axis);
}
