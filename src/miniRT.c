/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 14:51:55 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/11 12:47:09 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h> // REMOVE !!

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vec		*v;
	t_vec		*u;
	t_vec		*c;

	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	img = mlx_new_image(mlx, WIDTH / 2, HEIGHT / 2);
	if (!img)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_memset(img->pixels, 200, img->width * img->height * sizeof(int32_t));
	if (mlx_image_to_window(mlx, img, WIDTH / 4, HEIGHT / 4) < 0)
    {
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	// img->instances[0].x += WIDTH / 4;
	// img->instances[0].y += HEIGHT / 4;
	mlx_loop(mlx);
	ft_printf("Welcome to our miniRT\n");

	u = init_vec(1.0, 0.0, 1.0);
	v = init_vec(0.0, 1.0, 0.0);
	print_vec(v);
	print_vec(u);

	printf("Dot product: %f\n", dot(u, v));
	
	ft_printf("Cross product\n");
	c = cross(u, v);
	print_vec(c);
	
	return (0);
}