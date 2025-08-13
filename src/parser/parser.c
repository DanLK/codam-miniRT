/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser.c                                            :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/07 15:47:09 by hogu           #+#    #+#                */
/*   Updated: 2025/08/07 15:47:10 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static bool	get_params(const char *line, t_scene *scene)
{
	if (!line || !scene)
		return (0);
	if (ft_strncmp(line, "A ", 2) == 0)
		return (fill_in_ambient(line, scene));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (fill_in_camera(line, scene));
	else if (ft_strncmp(line, "L ", 2) == 0)
		return (fill_in_light(line, scene));
	else if (ft_strncmp(line, "sp ", 3) == 0)
		return (fill_in_sphere(line, scene));
	else if (ft_strncmp(line, "pl ", 3) == 0)
		return (fill_in_plane(line, scene));
	else if (ft_strncmp(line, "cy ", 3) == 0)
		return (fill_in_cylinder(line, scene));
	print_error(PARAM_TYPE, line);
	return (false);
}

static bool	handle_line(char *buffer, t_scene *scene)
{
	char	*trimmed;

	trimmed = ft_strtrim(buffer, " \t\n\r\f\v");
	free(buffer);
	if (!trimmed)
		return (printf("Error\n"), perror("malloc"), false);
	if (trimmed[0] == '\0')
		return (free(trimmed), true);
	if (!get_params(trimmed, scene))
		return (free(trimmed), false);
	return (free(trimmed), true);
}

bool	validate_elem(t_scene *scene)
{
	if (!scene->status.has_ambient)
		return (print_error(MISS_ELEM, "ambient"), false);
	if (!scene->status.has_camera)
		return (print_error(MISS_ELEM, "camera"), false);
	if (!scene->status.has_light)
		return (print_error(MISS_ELEM, "light"), false);
	if (!scene->status.has_sphere)
		return (print_error(MISS_ELEM, "sphere"), false);
	if (!scene->status.has_plane)
		return (print_error(MISS_ELEM, "plane"), false);
	if (!scene->status.has_cylinder)
		return (print_error(MISS_ELEM, "cylinder"), false);
	return (true);
}

bool	parser(t_scene *scene, const char *filename)
{
	int		fd;
	char	*buffer;
	char	*trimmed;

	if (!check_suffix(filename))
		return (print_error(WRONG_SUFFIX, NULL), false);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf("Error\n"), perror("Cannot open file"), false);
	buffer = get_next_line(fd);
	if (!buffer)
		return (close(fd), print_error(EMPTY_FILE, NULL), false);
	while (buffer)
	{
		if (!handle_line(buffer, scene))
			return (close(fd), false);
		buffer = get_next_line(fd);
	}
	if (!validate_elem(scene))
		return (close(fd), false);
	return (close(fd), true);
}
