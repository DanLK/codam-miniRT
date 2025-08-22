/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   util.c                                              :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/07 16:01:31 by hogu           #+#    #+#                */
/*   Updated: 2025/08/07 16:01:33 by hogu           ########   odam.nl        */
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

bool	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

const char	*skip_spaces(const char *s)
{
	while (*s && ft_isspace(*s))
		s++;
	return (s);
}

void	free_object_list(t_object *obj)
{
	t_object	*tmp;

	while (obj)
	{
		tmp = obj->next;
		if (obj->element)
			free(obj->element);
		free(obj);
		obj = tmp;
	}
}
