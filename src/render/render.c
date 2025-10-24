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
	t_object	*cur;
	double		t;
	double		t_min;

	hp->obj = NULL;
	t_min = DBL_MAX;
	cur = scene->objects;
	while (cur)
	{
		if (hit_object(ray, cur, &t) && t > EPSILON && t < t_min)
		{
			t_min = t;
			hp->obj = cur;
		}
		cur = cur->next;
	}
	if (!hp->obj)
		return (false);
	hp->t = t_min;
	hp->hp = ray_at(ray, t_min);
	hp->normal = get_normal(hp);
	if (dot(ray.dir, hp->normal) > 0.0)
		hp->normal = neg_vec(hp->normal);
	return (true);
}

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
