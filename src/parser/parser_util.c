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

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_scene(t_scene *scene)
{
	free_object_list(scene->objects);
	free_light_list(scene->light);
}
