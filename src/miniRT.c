/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 14:51:55 by dloustal      #+#    #+#                 */
/*   Updated: 2025/09/12 16:39:48 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vport		vp;
	t_scene	scene;

	//parsing
	if (argc != 2)
		return (print_error(WRONG_ARGS, NULL), EXIT_FAILURE);
	if (HEIGHT < 1)
		return (print_error(OUT_RANGE, "Image height"), EXIT_FAILURE);
	ft_bzero(&scene, sizeof(t_scene));
	if (!parser(&scene, argv[1]))
		return (EXIT_FAILURE);
	// print_scene(&scene);

	//mlx init
	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		free_object_list(scene.objects);
		free_light_list(scene.light);
		return (EXIT_FAILURE);
	}
	printf("Welcome to our miniRT\n");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		free_object_list(scene.objects);
		free_light_list(scene.light);
		mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}

	//vport
	make_vport(scene.camera, &vp);
	print_vport(&vp);
	
	//render
	if (SAMPLES == 1)
		render(img, &scene, &vp);
	else
		render_anti_aliasing(img, &scene, &vp);

	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
    {
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
 	free_object_list(scene.objects);
	free_light_list(scene.light);
	return (EXIT_SUCCESS);
}
