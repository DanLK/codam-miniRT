/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/19 13:36:40 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/27 12:30:42 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	paint_pixel(mlx_image_t *img, t_ray ray, t_scene *scene, int *pixel)
{
	t_object	*tmp;
	t_object	*closest;
	double		dist;
	double		dist_min;
	t_color		cl;

	closest = NULL;
	dist_min = DBL_MAX;
	tmp = scene->objects;
	while (tmp)
	{
		if (hit_object(ray, tmp, &dist) && dist < dist_min && dist > EPSILON)
		{
			dist_min = dist;
			closest = tmp;
		}
		tmp = tmp->next;
	}
	if (closest)
		cl = calc_obj_color(closest, scene, ray, dist_min);
	else
		cl = calc_background_color(ray);
	mlx_put_pixel(img, pixel[0], pixel[1], get_rgba(cl.r, cl.g, cl.b, 255));
}

/*used pointer *vp to avoid duplicating all data in vp struct,
	though it will not make a visible difference in speed. */

/*other changes: 
	1. renamed paint_gradientpix() to paint_pixel();
	2. packed i_h and i_w in pixel_coord[2], to pass into paint_pixel(), 
		limiting parameter count to 4. */

void	render(mlx_image_t *img, t_scene *scene, t_vport *vp)
{
	int			i_h;
	int			i_w;
	int			pixel_coord[2];
	t_coord		pixel_center;
	t_ray		ray;

	i_h = 0;
	while (i_h < (int)img->height)
	{
		i_w = 0;
		while (i_w < (int)img->width)
		{
			pixel_center = sum_vec(vp->p_00, sum_vec(scaled(vp->delta_x, i_w),
						scaled(vp->delta_y, i_h)));
			ray = set_ray(scene->camera.pos,
					sub_vec(pixel_center, scene->camera.pos));
			pixel_coord[0] = i_w;
			pixel_coord[1] = i_h;
			paint_pixel(img, ray, scene, pixel_coord);
			i_w++;
		}
		i_h++;
	}
}
