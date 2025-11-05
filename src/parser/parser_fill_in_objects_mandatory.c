/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser_fill_in_object_mandatory.c                   :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/10/17 12:18:19 by hogu           #+#    #+#                */
/*   Updated: 2025/10/17 12:18:20 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	fill_in_object(const char *s, t_scene *scene, t_parse_man_fn parse_man)
{
	char		**p;
	t_object	*obj;
	int			i_opt;

	if (!s || !scene)
		return (false);
	p = space_split(s);
	i_opt = 0;
	if (!parse_man(p, &obj, &i_opt))
		return (free_split(p), false);
	if (p[i_opt])
	{
		print_error(PARAM_COUNT, s);
		return (free(obj), free_split(p), false);
	}
	append_object(&scene->objects, obj);
	return (free_split(p), true);
}
