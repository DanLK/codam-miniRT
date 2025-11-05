/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   event.c                                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/09/11 13:59:19 by hogu           #+#    #+#                */
/*   Updated: 2025/09/11 13:59:20 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	esc_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
}

void	close_hook(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	mlx_close_window(mlx);
}
