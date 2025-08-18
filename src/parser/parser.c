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

static bool	match_identifier(const char *line, const char *id)
{
	int	len;

	len = ft_strlen(id);
	if (ft_strncmp(line, id, len) != 0 || !ft_isspace(line[len]))
		return (false);
	return (true);
}

static bool	get_params(const char *line, t_scene *scene)
{
	if (!line || !scene)
		return (0);
	if (match_identifier(line, "A"))
		return (fill_in_ambient(line, scene));
	else if (match_identifier(line, "C"))
		return (fill_in_camera(line, scene));
	else if (match_identifier(line, "L"))
		return (fill_in_light(line, scene));
	else if (match_identifier(line, "sp"))
		return (fill_in_sphere(line, scene));
	else if (match_identifier(line, "pl"))
		return (fill_in_plane(line, scene));
	else if (match_identifier(line, "cy"))
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

static void	gnl_drain(int fd)
{
	char	*tmp;

	tmp = get_next_line(fd);
	while (tmp)
	{
		free(tmp);
		tmp = get_next_line(fd);
	}
	close(fd);
}

bool	parser(t_scene *scene, const char *filename)
{
	int		fd;
	char	*buffer;

	if (!check_suffix(filename))
		return (print_error(WRONG_SUFFIX, NULL), false);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (printf("Error\n"), perror("Cannot open file"), false);
	buffer = get_next_line(fd);
	if (!buffer)
		return (gnl_drain(fd), print_error(EMPTY_FILE, NULL), false);
	while (buffer)
	{
		if (!handle_line(buffer, scene))
			return (gnl_drain(fd), free_object_list(scene->objects), false);
		buffer = get_next_line(fd);
	}
	if (!validate_elem(scene))
		return (gnl_drain(fd), free_object_list(scene->objects), false);
	return (close(fd), true);
}
