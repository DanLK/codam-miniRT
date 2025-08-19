/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 16:03:41 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/19 12:07:09 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	ray_at(t_ray ray, double t)
{
	t_coord	pos;

	pos = sum_vec(ray.origin, scaled(ray.dir, t));
	return (pos);
}

t_vec	prim_ray_dir(t_camera cam, t_coord pixel)
{
	t_vec	prim_ray_dir;

	prim_ray_dir.x = pixel.x - cam.pos.x;
	prim_ray_dir.y = pixel.y - cam.pos.y;
	prim_ray_dir.z = pixel.z - cam.pos.z;
	return (prim_ray_dir);
}

t_ray	set_ray(t_camera cam, t_vec prim_ray_dir)
{
	t_ray	ray;

	ray.dir = prim_ray_dir;
	ray.origin = cam.pos;
	return (ray);
}

static void	paint_gradientpix(mlx_image_t *img, t_ray ray, t_object *objs)
{
	t_object	closest;
	double		dist;
	double		dist_min;
	t_color		color;

	closest = NULL;
	dist_min = DBL_MAX;
	while (objs)
	{
		if (hit_object(ray, obj, &dist) && dist < dist_min && dist > EPSILON)
		{
			dist_min = t;
			closest = obj;
		} 
		obj = objs->next;
	}
	if (closest)
		color = get_obj_color(closest, scene);
	else
		color = get_backgrount_color(scene);
	{
		unit_dir = normalized(ray.dir);
		a = 0.5 * (unit_dir.y + 1.0);
		// a = (unit_dir.y + 0.75) / 1.5;
		color.r = (1 - a) * 255 + a * 25;
		color.g = (1 - a) * 255 + a * 25;
		color.b = (1 - a) * 255 + a * 112;
	}
	mlx_put_pixel(img, x, y, get_rgba(color.r, color.g, color.b, 255));
	// if (counter % 2048 == 0)
	// 			print_vec(&unit_dir, "unit");
	(void)counter;
}

void	paint_raygradient(mlx_image_t *img, t_camera cam, t_vport vp)
{
	int			i_h;
	int			i_w;
	t_coord		pixel_center;
	t_ray		ray;
	int			counter;

	i_h = 0;
	counter = 0;
	while (i_h < (int)img->height)
	{
		i_w = 0;
		while (i_w < (int)img->width)
		{
			pixel_center = sum_vec(vp.p_00, sum_vec(scaled(vp.delta_x, i_w),
				scaled(vp.delta_y, i_h)));
			ray = set_ray(cam, prim_ray_dir(cam, pixel_center));
			paint_gradientpix(img, ray, i_w, i_h, counter);
			counter++;
			// if (counter % 2048 == 0)
			// 	print_vec(&ray.dir, "ray");
			i_w++;
		}
		i_h++;
	}

}
