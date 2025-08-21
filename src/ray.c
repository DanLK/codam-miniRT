/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 16:03:41 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/21 15:52:23 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	ray_at(t_ray ray, double t)
{
	t_coord	pos;

	pos = sum_vec(ray.origin, scaled(ray.dir, t));
	return (pos);
}

// here I deleted t_vec prim_ray_dir(t_camera cam, t_coord pixel)
// because it is exactly the same as sub_vec(), and the latter is more universal

t_ray	set_ray(t_coord start, t_vec ray_dir)
{
	t_ray	ray;

	ray.dir = normalized(ray_dir); // so that ray.dir is always normalized
	ray.origin = start;
	return (ray);
}

static void	paint_gradientpix(mlx_image_t *img, t_ray ray, t_scene *scene, int x, int y) // changed parameter t_object to t_scene, for get_obj_color() 
{
	t_object	*tmp;
	t_object	*closest;
	double		dist;
	double		dist_min;
	t_color		color;

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
		color = get_object_color(closest, scene, ray, dist);
	else
		color = get_background_color(ray);
	mlx_put_pixel(img, x, y, get_rgba(color.r, color.g, color.b, 255));
}

void	paint_raygradient(mlx_image_t *img, t_scene *scene, t_vport *vp)
{
	int			i_h;
	int			i_w;
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
			ray = set_ray(scene->camera.pos, sub_vec(pixel_center, scene->camera.pos));
			paint_gradientpix(img, ray, scene, i_w, i_h);
			// if (counter % 2048 == 0)
			// 	print_vec(&ray.dir, "ray");
			i_w++;
		}
		i_h++;
	}
}
