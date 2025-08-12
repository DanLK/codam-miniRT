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

#include "../include/miniRT.h"

bool	fill_in_ambient(const char *line, t_scene *scene)
{
	char	**params;
	double	ratio;

	if (!line || !scene)
		return (false);
	params = ft_split(line, ' ');
	if (!params || !params[1] || !params[2] || params[3])
		return (print_error(PARAM_COUNT, line), free_split(params), false);
	if (!ft_atod(params[1], &ratio))
		return (print_error(DOUBLE, params[1]), free_split(params), false);
	if (check_range(ratio, 0.0, 1.0))
		scene->ambient.ratio = ratio;
	else
		return (print_error(OUT_RANGE, params[1]), free_split(params), false);
	if (!check_color(params[2], &scene->ambient.color))
		return (free_split(params), false);
	return (free_split(params), true);
}

bool	fill_in_camera(const char *line, t_scene *scene)
{
	char	**params;
	int		fov;

	if (!line || !scene)
		return (false);
	params = ft_split(line, ' ');
	if (!params || !params[1] || !params[2] || !params[3] || params[4])
		return (print_error(PARAM_COUNT, line), free_split(params), false);
	if (!check_coord(params[1], &scene->camera.pos)
		|| !check_vector(params[2], &scene->camera.dir)
		|| !ft_atoi_strict(params[3], &fov, 180))
		return (free_split(params), false);
	scene->camera.fov = fov;
	return (free_split(params), true);
}
