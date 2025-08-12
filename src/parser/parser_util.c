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

#include "../include/miniRT.h"

bool	check_range(double value, double min, double max)
{
	return (value > min - EPSILON && value < max + EPSILON);
}

bool	check_equal(double value, double target)
{
	return (fabs(value - target) < EPSILON);
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

const char	*skip_spaces(const char *s)
{
	while (*s && (*s == ' ' || *s == '\f' || *s == '\n'
			|| *s == '\r' || *s == '\t' || *s == '\v'))
		s++;
	return (s);
}
