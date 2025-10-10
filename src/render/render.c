/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/19 13:36:40 by dloustal      #+#    #+#                 */
/*   Updated: 2025/10/10 13:35:29 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	find_closest_hit(t_ray ray, t_scene *scene, t_hit_point *hp)
{
	t_object	*closest;
	t_object	*cur;
	double		t;
	double		t_min;

	closest = NULL;
	t_min = DBL_MAX;
	cur = scene->objects;
	while (cur)
	{
		if (hit_object(ray, cur, &t) && t > EPSILON && t < t_min)
		{
			t_min = t;
			closest = cur;
		}
		cur = cur->next;
	}
	if (!closest)
		return (false);
	hp->obj = closest;
	hp->t = t_min;
	hp->hp = ray_at(ray, t_min);
	hp->normal = get_normal(closest, hp->hp);
	return (true);
}

// bool	find_closest_hit(t_ray ray, t_scene *scene, t_object **out_obj,
// 	double *out_t_min)
// {
// 	t_object	*closest;
// 	t_object	*cur;
// 	double		t;
// 	double		t_min;

// 	closest = NULL;
// 	t_min = DBL_MAX;
// 	cur = scene->objects;
// 	while (cur)
// 	{
// 		if (hit_object(ray, cur, &t) && t > EPSILON && t < t_min)
// 		{
// 			t_min = t;
// 			closest = cur;
// 		}
// 		cur = cur->next;
// 	}
// 	if (!closest)
// 		return (false);
// 	*out_obj = closest;
// 	*out_t_min = t_min;
// 	return (true);
// }

static t_ray	sample_camera_ray(int w, int h, t_vport *vp, t_scene *scene)
{
	t_vec	offset;
	t_coord	pixel_sample;
	t_ray	ray;

	if (SAMPLES == 1)
		offset = vec(0.0, 0.0, 0.0);
	else
		offset = vec(random_double() - 0.5, random_double() - 0.5, 0.0);
	pixel_sample = sum_vec(vp->p_00, sum_vec(scaled(vp->delta_x, w + offset.x),
				scaled(vp->delta_y, h + offset.y)));
	ray = set_ray(scene->camera.pos, sub_vec(pixel_sample, scene->camera.pos));
	return (ray);
}


void	render_image(mlx_image_t *img, t_scene *scene, t_vport *vp)
{
	int		i_h;
	int		i_w;
	int		k;
	t_color	cl;
	t_ray	ray;

	i_h = 0;
	while (i_h < (int)img->height)
	{
		i_w = 0;
		while (i_w < (int)img->width)
		{
			k = 0;
			cl = color(0.0, 0.0, 0.0);
			while (k++ < SAMPLES)
			{
				ray = sample_camera_ray(i_w, i_h, vp, scene);
				cl = col_sum(cl, trace_color(ray, ray, scene, DEPTH));
			}
			cl = col_scale(cl, 1.0 / (double)SAMPLES);
			mlx_put_pixel(img, i_w, i_h, get_rgba(cl, 1.0));
			i_w++;
		}
		i_h++;
	}
}

// static t_color	get_color(t_ray ray, t_scene *scene)
// {
// 	t_object	*tmp;
// 	t_object	*closest;
// 	double		dist;
// 	double		dist_min;
// 	t_color		cl;

// 	closest = NULL;
// 	dist_min = DBL_MAX;
// 	tmp = scene->objects;
// 	while (tmp)
// 	{
// 		if (hit_object(ray, tmp, &dist) && dist < dist_min && dist > EPSILON)
// 		{
// 			dist_min = dist;
// 			closest = tmp;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (closest)
// 		cl = calc_obj_color(closest, scene, ray, dist_min);
// 	else
// 		cl = calc_background_color(ray);
// 	return (cl);
// }

// static t_color	compute_color(t_ray ray, t_scene *scene)
// {
// 	t_color	cl;

// 	if (DEPTH == 1)
// 		cl = get_color(ray, scene);
// 	else
// 		cl = get_color_deep(ray, ray, scene, DEPTH);
// 	return (cl);
// }

// /*Rendering with all materials at 50% color absorption with(out) antialiasing*/
// void	render_aa_deep(mlx_image_t *img, t_scene *scene, t_vport *vp)
// {
// 	int			i_h;
// 	int			i_w;
// 	t_color		cl;
// 	t_ray		ray;
// 	int			k;

// 	i_h = 0;
// 	while (i_h < (int)img->height)
// 	{
// 		i_w = 0;
// 		while (i_w < (int)img->width)
// 		{
// 			k = 0;
// 			cl = color(0.0, 0.0, 0.0);
// 			while (k++ < SAMPLES)
// 			{
// 				ray = get_ray(i_w, i_h, vp, scene);
// 				cl = col_sum(cl, compute_color(ray, scene));
// 			}
// 			cl = col_scale(cl, 1.0 / SAMPLES);
// 			mlx_put_pixel(img, i_w, i_h, get_rgba(cl, 255));
// 			i_w++;
// 		}
// 		i_h++;
// 	}
// }
// t_color	get_color_deep(t_ray ray, t_ray ray2, t_scene *scene, int depth)
// {
// 	t_object	*tmp;
// 	t_object	*closest;
// 	double		dist;
// 	double		dist_min;
// 	t_coord		hit_point;
// 	t_vec		offset_point;
// 	t_vec		random_dir;
// 	t_vec		normal;
// 	t_color		rec_cl; // recursive color
// 	t_color		cl;

// 	if (depth <= 0)
// 		return (color(0.0, 0.0, 0.0));
// 	closest = NULL;
// 	dist_min = DBL_MAX;
// 	tmp = scene->objects;
// 	while (tmp)
// 	{
// 		if (hit_object(ray, tmp, &dist) && dist < dist_min && dist > EPSILON)
// 		{
// 			dist_min = dist;
// 			hit_point = ray_at(ray, dist_min);
// 			closest = tmp;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (closest)
// 	{
// 		normal = get_normal(closest, hit_point);
// 		offset_point = sum_vec(hit_point, scaled(normal, 1e-6));
// 		random_dir = sum_vec(normal, random_unit_vec());
// 		rec_cl = col_scale(get_color_deep(set_ray(offset_point, random_dir), ray2,
//             scene, depth - 1), 0.15);
// 		cl = col_sum(rec_cl, calc_obj_color(closest, scene, ray2, dist_min));
// 	}
// 	else
// 		cl = calc_background_color(ray);
// 	return (cl);
// }

// t_ray	get_ray(int w, int h, t_vport *vp, t_scene *scene)
// {
// 	t_vec	offset;
// 	t_coord	pixel_center;
// 	t_ray	ray;

// 	offset = sample_square();
// 	pixel_center = sum_vec(vp->p_00, sum_vec(scaled(vp->delta_x, w + offset.x),
// 						scaled(vp->delta_y, h + offset.y)));
// 	ray = set_ray(scene->camera.pos,
// 					sub_vec(pixel_center, scene->camera.pos));
// 	return (ray);
// }

// t_vec	sample_square(void)
// {
// 	return (vec(random_double() - 0.5, random_double() - 0.5, 0));
// }
