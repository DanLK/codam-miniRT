/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 14:51:55 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/21 15:52:05 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	// Paint a gradient
	// t_vec		*c_topright;
	// t_vec		*c_botleft;
	// u_int32_t	w;
	// uint32_t	h;
	// int			r;
	// int			g;
	// int			b;
	// Experiments with the viewport
	t_vport		vp;
	// int			i_h;
	// int			i_w;
	// t_coord		pixel_center;
	// t_ray		ray;
	// int			counter;
	t_scene	scene;

	//parsing
	if (argc != 2)
		return (print_error(WRONG_ARGS, NULL), EXIT_FAILURE);
	if (HEIGHT < 1) // I'll prepare a error_msg for this
		return (1);
	ft_bzero(&scene, sizeof(t_scene));
	if (!parser(&scene, argv[1]))
		return (free_object_list(scene.objects), EXIT_FAILURE);
	print_scene(&scene);

	//mlx init
	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		free_object_list(scene.objects);
		return (EXIT_FAILURE);
	}
	printf("Welcome to our miniRT\n");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		free_object_list(scene.objects);
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}

	//vport
	make_vport(scene.camera, &vp);
	print_vport(&vp);
	
	//render
	paint_raygradient(img, &scene, &vp);

	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
    {
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	// free(c_botleft);
	// free(c_topright);
 	free_object_list(scene.objects);
	return (0);
}
