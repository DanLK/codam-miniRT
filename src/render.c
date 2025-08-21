/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/19 13:36:40 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/21 12:00:04 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// static void	paint_gradientpix(mlx_image_t *img, t_ray ray, t_object *objs)
// {
// 	t_object	closest;
// 	double		dist;
// 	double		dist_min;
// 	t_color		color;

// 	closest = NULL;
// 	dist_min = DBL_MAX;
// 	while (objs)
// 	{
// 		if (hit_object(ray, obj, &dist) && dist < dist_min && dist > EPSILON)
// 		{
// 			dist_min = t;
// 			closest = obj;
// 		} 
// 		obj = objs->next;
// 	}
// 	if (closest)
// 		color = get_obj_color(closest, scene);
// 	else
// 		color = get_background_color(scene);
// 	{
// 		unit_dir = normalized(ray.dir);
// 		a = 0.5 * (unit_dir.y + 1.0);
// 		// a = (unit_dir.y + 0.75) / 1.5;
// 		color.r = (1 - a) * 255 + a * 25;
// 		color.g = (1 - a) * 255 + a * 25;
// 		color.b = (1 - a) * 255 + a * 112;
// 	}
// 	mlx_put_pixel(img, x, y, get_rgba(color.r, color.g, color.b, 255));
// 	// if (counter % 2048 == 0)
// 	// 			print_vec(&unit_dir, "unit");
// }

static void	paint_gradientpix(mlx_image_t *img, t_ray ray, t_object *objs, int x, int y)
{
	t_object	*closest;
	t_object	*current;
	double		dist;
	double		dist_min;
	t_color		color;
	t_vec		unit_dir;
	double		a;

	closest = NULL;
	current = objs;
	dist_min = DBL_MAX;
	while (current != NULL)
	{
		printf("OBJS not null\n");
		if (hit_object(ray, current, &dist) && dist < dist_min && dist > EPSILON)
		{
			printf("HIT SPHERE\n");
			dist_min = dist;
			closest = current;
		} 
		printf("objs->next == null: [%d]\n", current->next == NULL);
		printf("current == null: [%d]\n", current == NULL);
		// printf("objs->next->type: [%d]\n", objs->next->type);
		current = current->next;
		printf("current == null: [%d]\n", current == NULL);
		// exit(1);
	}
	// if (closest)
	// 	// color = closest->element.color;
	// 	// color = get_obj_color(closest, scene);
	// {
	// 	color.r = 255;
	// 	color.g = 0;
	// 	color.b = 0;
	// }
	// else
	// 	color = get_background_color(scene);
	if (true)
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
}

static t_object	get_objs(void)
{
	t_sphere	sphere;
	t_object	objs;

	sphere.center = vec(0, 0, 10);
	sphere.diameter = 10;
	objs.element = &sphere;
	objs.type = SPHERE;
	objs.next = NULL;
	return (objs);
}

void	render(mlx_image_t *img, t_camera cam, t_vport vp)
{
	int			i_h;
	int			i_w;
	t_coord		pixel_center;
	t_ray		ray;
	int			counter;
	t_object	objs;

	i_h = 0;
	counter = 0;
	objs = get_objs();
	while (i_h < (int)img->height)
	{
		i_w = 0;
		while (i_w < (int)img->width)
		{
			pixel_center = sum_vec(vp.p_00, sum_vec(scaled(vp.delta_x, i_w),
				scaled(vp.delta_y, i_h)));
			ray = set_ray(cam, prim_ray_dir(cam, pixel_center));
			paint_gradientpix(img, ray, &objs, i_w, i_h);
			counter++;
			// if (counter % 2048 == 0)
			// 	print_vec(&ray.dir, "ray");
			i_w++;
		}
		i_h++;
	}

}