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

static bool	alloc_object(t_object **obj)
{
	*obj = (t_object *)malloc(sizeof(t_object));
	if (!*obj)
		return (printf("Error\n"), perror("malloc"), false);
	ft_bzero(*obj, sizeof(t_object));
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
	if (diameter < 0)
		return (print_error(OUT_RANGE, params[2]), free(obj),
			free_split(params), false);
	obj->sp.diameter = diameter;
	obj->type = SPHERE;
	append_object(&scene->objects, obj);
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
	return (free_split(params), true);
}

bool	fill_in_cylinder(const char *s, t_scene *scene)
{
	char		**p;
	t_object	*obj;
	double		diameter;
	double		height;

	if (!s || !scene)
		return (false);
	p = space_split(s);
	if (!p || !p[1] || !p[2] || !p[3] || !p[4] || !p[5] || p[6])
		return (print_error(PARAM_COUNT, s), free_split(p), false);
	if (!alloc_object(&obj))
		return (free_split(p), false);
	if (!check_coord(p[1], &obj->center) || !check_color(p[5], &obj->color)
		|| !check_vector(p[2], &(obj->cy.dir)))
		return (free(obj), free_split(p), false);
	if (!ft_atod(p[3], &diameter) || !ft_atod(p[4], &height))
		return (print_error(DOUBLE, "cy:d/h"), free(obj), free_split(p), false);
	if (diameter < 0 || height < 0)
		return (print_error(OUT_RANGE, "cy:d/h"), free(obj),
			free_split(p), false);
	obj->cy.diameter = diameter;
	obj->cy.height = height;
	obj->type = CYLINDER;
	return (append_object(&scene->objects, obj), free_split(p), true);
}
