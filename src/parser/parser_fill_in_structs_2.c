/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_fill_in_structs_2.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/13 12:27:58 by hogu          #+#    #+#                 */
/*   Updated: 2025/08/27 12:29:19 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	append_object(t_object **list, t_object *new)
{
	t_object	*cur;

	if (!list || !new)
		return ;
	if (!*list)
	{
		*list = new;
		return ;
	}
	cur = *list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

static bool	alloc_object(t_object **obj)
{
	*obj = (t_object *)malloc(sizeof(t_object));
	if (!*obj)
		return (printf("Error\n"), perror("malloc"), false);
	(*obj)->next = NULL;
	return (true);
}

bool	fill_in_sphere(const char *s, t_scene *scene)
{
	char		**params;
	t_object	*obj;
	double		diameter;

	if (!s || !scene)
		return (false);
	params = space_split(s);
	if (!params || !params[1] || !params[2] || !params[3] || params[4])
		return (print_error(PARAM_COUNT, s), free_split(params), false);
	if (!alloc_object(&obj))
		return (free_split(params), false);
	if (!check_coord(params[1], &obj->center)
		|| !check_color(params[3], &obj->color))
		return (free(obj), free_split(params), false);
	if (!ft_atod(params[2], &diameter))
		return (print_error(DOUBLE, params[2]), free(obj),
			free_split(params), false);
	obj->sp.diameter = diameter;
	obj->type = SPHERE;
	append_object(&scene->objects, obj);
	scene->status.has_sphere = true;
	return (free_split(params), true);
}

bool	fill_in_plane(const char *s, t_scene *scene)
{
	char		**params;
	t_object	*obj;

	if (!s || !scene)
		return (false);
	params = space_split(s);
	if (!params || !params[1] || !params[2] || !params[3] || params[4])
		return (print_error(PARAM_COUNT, s), free_split(params), false);
	if (!alloc_object(&obj))
		return (free_split(params), false);
	if (!check_coord(params[1], &obj->center)
		|| !check_vector(params[2], &(obj->pl.dir))
		|| !check_color(params[3], &obj->color))
		return (free(obj), free_split(params), false);
	obj->type = PLANE;
	append_object(&scene->objects, obj);
	scene->status.has_plane = true;
	return (free_split(params), true);
}

bool	fill_in_cylinder(const char *s, t_scene *scene)
{
	char		**pr;
	t_object	*obj;
	double		diameter;
	double		height;

	if (!s || !scene)
		return (false);
	pr = space_split(s);
	if (!pr || !pr[1] || !pr[2] || !pr[3] || !pr[4] || !pr[5] || pr[6])
		return (print_error(PARAM_COUNT, s), free_split(pr), false);
	if (!alloc_object(&obj))
		return (free_split(pr), false);
	if (!check_coord(pr[1], &obj->center) || !check_vector(pr[2], &(obj->cy.dir))
		|| !check_color(pr[5], &obj->color))
		return (free(obj), free_split(pr), false);
	if (!ft_atod(pr[3], &diameter) || !ft_atod(pr[4], &height))
		return (print_error(DOUBLE, "diameter or height"), free(obj),
			free_split(pr), false);
	obj->cy.diameter = diameter;
	obj->cy.height = height;
	obj->type = CYLINDER;
	scene->status.has_cylinder = true;
	return (append_object(&scene->objects, obj), free_split(pr), true);
}
