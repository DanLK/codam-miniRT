/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 14:51:55 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/21 16:13:33 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	init_scene(t_scene *scene, int argc, char *argv[])
{
	if (argc != 2)
		return (print_error(WRONG_ARGS, NULL), false);
	if (HEIGHT < 1)
		return (print_error(OUT_RANGE, "Image height"), false);
	ft_bzero(scene, sizeof(t_scene));
	if (!parser(scene, argv[1]))
		return (false);
	return (true);
}

static bool	init_mlx(mlx_t **mlx, mlx_image_t **img)
{
	*mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!*mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (false);
	}
	*img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (!*img)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		mlx_terminate(*mlx);
		return (false);
	}
	return (true);
}

static bool	render_scene(mlx_t *mlx, mlx_image_t *img, t_scene *scene,
		t_vport *vp)
{
	make_vport(scene->camera, vp);
	render(img, scene, vp);
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (false);
	}
	return (true);
}

static void	run_loop(mlx_t *mlx, t_scene *scene)
{
	mlx_key_hook(mlx, esc_hook, mlx);
	mlx_close_hook(mlx, close_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_scene(scene);
}

int	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vport		vp;
	t_scene		scene;

	mlx = NULL;
	img = NULL;
	if (!init_scene(&scene, argc, argv)
		|| !init_mlx(&mlx, &img)
		|| !render_scene(mlx, img, &scene, &vp))
	{
		free_scene(&scene);
		if (mlx)
			mlx_terminate(mlx);
		return (EXIT_FAILURE);
	}
	run_loop(mlx, &scene);
	return (EXIT_SUCCESS);
}
