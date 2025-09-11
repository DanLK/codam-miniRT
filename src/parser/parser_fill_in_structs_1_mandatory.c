/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser_fill_in_structs_1.c                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/12 15:52:00 by hogu           #+#    #+#                */
/*   Updated: 2025/08/12 15:52:01 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	validate_elem(t_scene *scene)
{
	if (!scene->status.has_ambient)
		return (print_error(MISS_ELEM, "ambient"), false);
	if (!scene->status.has_camera)
		return (print_error(MISS_ELEM, "camera"), false);
	if (!scene->status.has_light)
		return (print_error(MISS_ELEM, "light"), false);
	return (true);
}

bool	fill_in_ambient(const char *s, t_scene *scene)
{
	char	**params;

	if (!s || !scene)
		return (false);
	if (scene->status.has_ambient)
		return (print_error(DUP_ELEM, "ambient"), false);
	params = space_split(s);
	if (!params || !params[1] || !params[2] || params[3])
		return (print_error(PARAM_COUNT, s), free_split(params), false);
	if (!check_ratio(params[1], &scene->ambient.ratio)
		|| !check_color(params[2], &scene->ambient.color))
		return (free_split(params), false);
	scene->status.has_ambient = true;
	return (free_split(params), true);
}

bool	fill_in_camera(const char *s, t_scene *scene)
{
	char	**params;
	int		fov;

	if (!s || !scene)
		return (false);
	if (scene->status.has_camera)
		return (print_error(DUP_ELEM, "camera"), false);
	params = space_split(s);
	if (!params || !params[1] || !params[2] || !params[3] || params[4])
		return (print_error(PARAM_COUNT, s), free_split(params), false);
	if (!check_coord(params[1], &scene->camera.pos)
		|| !check_vector(params[2], &scene->camera.dir)
		|| !ft_atoi_strict(params[3], &fov, 180))
		return (free_split(params), false);
	scene->camera.fov = fov;
	scene->status.has_camera = true;
	return (free_split(params), true);
}

static bool	alloc_light(t_light **light)
{
	*light = (t_light *)malloc(sizeof(t_light));
	if (!*light)
		return (printf("Error\n"), perror("malloc"), false);
	ft_bzero(*light, sizeof(t_light));
	(*light)->next = NULL;
	return (true);
}

bool	fill_in_light(const char *s, t_scene *scene)
{
	char	**params;
	t_light	*light;

	if (!s || !scene)
		return (false);
	if (scene->status.has_light)
		return (print_error(DUP_ELEM, "light"), false);
	params = space_split(s);
	if (!params || !params[1] || !params[2] || !params[3] || params[4])
		return (print_error(PARAM_COUNT, s), free_split(params), false);
	if (!alloc_light(&light))
		return (free_split(params), false);
	if (!check_coord(params[1], &light->pos)
		|| !check_ratio(params[2], &light->ratio)
		|| !check_color(params[3], &light->color))
		return (free(light), free_split(params), false);
	append_light(&scene->light, light);
	scene->status.has_light = true;
	return (free_split(params), true);
}
