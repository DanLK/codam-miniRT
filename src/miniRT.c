/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 14:51:55 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/11 15:48:06 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main(void)
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