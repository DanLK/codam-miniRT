/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_util.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 16:01:31 by hogu          #+#    #+#                 */
/*   Updated: 2025/08/27 12:29:29 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	check_range(double value, double min, double max)
{
	return (value > min - EPSILON && value < max + EPSILON);
}

bool	check_equal(double value, double target)
{
	return (fabs(value - target) < EPSILON);
}

const char	*skip_spaces(const char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	return (s);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	if (scene->objects)
		free_object_list(scene->objects);
	if (scene->light)
		free_light_list(scene->light);
}
