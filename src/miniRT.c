/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 14:51:55 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/15 13:27:18 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	// Paint a gradient
	t_vec		*c_topright;
	t_vec		*c_botleft;
	u_int32_t	w;
	uint32_t	h;
	int			r;
	int			g;
	int			b;
	// Experiments with the viewport
	t_camera	cam;
	t_vport		vp;
	int			i_h;
	int			i_w;
	t_coord		pixel_center;
	t_ray		ray;
	int			counter;

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
	cam.pos.x = 0;
	cam.pos.y = 0;
	cam.pos.z = 0;
	cam.dir.x = 0;
	cam.dir.y = 0;
	cam.dir.z = 10;
	cam.fov = 90;

	make_vport(cam, &vp);
	printf("VP width: %f\n", vp.width);
	printf("VP height: %f\n", vp.height);
	printf("VP ratio: %f\n", vp.ratio);
	// printf("w: %d h: %d  ratio: %f w/h: %f\n", WIDTH, HEIGHT, RATIO, (double)WIDTH / HEIGHT);
	print_vec(&cam.pos, "cam_pos");
	print_vec(&vp.v_right, "right");
	print_vec(&vp.v_down, "down");
	print_vec(&vp.p_00, "p(0,0)");
	i_h = 0;
	counter = 0;
	while (i_h < HEIGHT)
	{
		i_w = 0;
		while (i_w < WIDTH)
		{
			pixel_center = sum_vec(vp.p_00, sum_vec(scaled(vp.delta_x, i_w), scaled(vp.delta_y, i_h)));
			ray = set_ray(cam, prim_ray_dir(cam, pixel_center));
			counter++;
			if (counter % 2048 == 0)
				print_vec(&ray.dir, "ray");
			i_w++;
		}
		i_h++;
	}

	
	
	//Paint a rectangle in the center with a color gradient
	c_botleft = init_vec(0,191,255);
	c_topright = init_vec(255, 20, 147);
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
// 	t_scene	scene;

// 	ft_bzero(&scene, sizeof(t_scene));
// 	if (argc != 2)
// 		return (print_error(WRONG_ARGS, NULL), EXIT_FAILURE);
// 	if (!parser(&scene, argv[1]))
// 		return (EXIT_FAILURE);
// 	//execute
// 	return (EXIT_SUCCESS);
// }
