/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 14:51:55 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/13 15:28:43 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_vec		*c_topright;
	t_vec		*c_botleft;
	u_int32_t	w;
	uint32_t	h;
	int			r;
	int			g;
	int			b;
	// t_camera	*cam;

	if (HEIGHT < 1)
		return (1);
	mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	printf("Welcome to our miniRT\n");
	img = mlx_new_image(mlx, WIDTH / 2, HEIGHT / 2);
	if (!img)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	// Start experimenting with the viewport
	// cam = malloc(sizeof(t_camera));
	// if (!cam)
	// 	exit(EXIT_FAILURE);
	// cam->pos = *init_vec(0, 0, 0);
	// cam->dir = *init_vec(0, 0, -1); //Should not allocate memory for this
	
	//Paint a rectangle in the center with a color gradient
	c_botleft = init_vec(138, 43, 226);
	c_topright = init_vec(255, 255, 0);
	w = 0;
	while (w < img->width)
	{
		h = 0;
		while (h < img->height)
		{
			r = (int)((((double)w / (img->width - 1)) * c_topright->x + ((double)h / (img->height - 1)) * c_botleft->x) / 2.0);
			g = (int)((((double)w / (img->width - 1)) * c_topright->y + ((double)h / (img->height - 1)) * c_botleft->y) / 2.0);
			b = (int)((((double)w / (img->width - 1)) * c_topright->z + ((double)h / (img->height - 1)) * c_botleft->z) / 2.0);
			mlx_put_pixel(img, w, h, get_rgba(r, g, b, 255));
			// printf("x: %d, y: %d\n", w, h);
			h++;
		}
		w++;
	}
	//------------------------------------------------------------------------------
	if (mlx_image_to_window(mlx, img, WIDTH / 4, HEIGHT / 4) < 0)
    {
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free(c_botleft);
	free(c_topright);
	
	return (0);
}
	t_scene	scene;

	ft_bzero(&scene, sizeof(t_scene));
	if (argc != 2)
		return (print_error(WRONG_ARGS, NULL), EXIT_FAILURE);
	if (!parser(&scene, argv[1]))
		return (EXIT_FAILURE);
	//execute
	return (EXIT_SUCCESS);
}
