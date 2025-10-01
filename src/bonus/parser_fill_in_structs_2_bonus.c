/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_fill_in_structs_2_bonus.c                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/03 16:22:22 by hogu          #+#    #+#                 */
/*   Updated: 2025/10/01 17:14:54 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static bool	alloc_object(t_object **obj)
{
	*obj = (t_object *)malloc(sizeof(t_object));
	if (!*obj)
		return (printf("Error\n"), perror("malloc"), false);
	ft_bzero(*obj, sizeof(t_object));
	((*obj)->material).type = DEFAULT;
	((*obj)->material).albedo = 1.0;
	(*obj)->next = NULL;
	return (true);
}

bool	fill_in_sphere(const char *s, t_scene *scene)
{
	char		**pr;
	t_object	*obj;
	double		diameter;

	if (!s || !scene)
		return (false);
	pr = space_split(s);
	if (!pr || !pr[1] || !pr[2] || !pr[3] || !pr[4] || (pr[5] && !pr[6]) || pr[7])
		return (print_error(PARAM_COUNT, s), free_split(pr), false);
	if (!alloc_object(&obj))
		return (free_split(pr), false);
	if (!check_coord(pr[1], &obj->center) || !check_color(pr[3], &obj->color)
		|| !check_chkb(pr[4], &obj->is_chkb)
		|| (pr[5] && !check_material(pr[5], pr[6], &obj->material)))
		return (free(obj), free_split(pr), false);
	if (!ft_atod(pr[2], &diameter))
		return (print_error(DOUBLE, pr[2]), free(obj), free_split(pr), false);
	if (diameter < 0)
		return (print_error(OUT_RANGE, pr[2]), free(obj),
			free_split(pr), false);
	obj->sp.diameter = diameter;
	obj->type = SPHERE;
	append_object(&scene->objects, obj);
	return (free_split(pr), true);
}

bool	fill_in_plane(const char *s, t_scene *scene)
{
	char		**params;
	t_object	*obj;

	if (!s || !scene)
		return (false);
	params = space_split(s);
	if (!params || !params[1] || !params[2] || !params[3] || !params[4]
		|| params[5])
		return (print_error(PARAM_COUNT, s), free_split(params), false);
	if (!alloc_object(&obj))
		return (free_split(params), false);
	if (!check_coord(params[1], &obj->center)
		|| !check_vector(params[2], &(obj->pl.dir))
		|| !check_color(params[3], &obj->color)
		|| !check_chkb(params[4], &obj->is_chkb))
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
	if (!p || !p[1] || !p[2] || !p[3] || !p[4] || !p[5] || !p[6] || p[7])
		return (print_error(PARAM_COUNT, s), free_split(p), false);
	if (!alloc_object(&obj))
		return (free_split(p), false);
	if (!check_coord(p[1], &obj->center) || !check_color(p[5], &obj->color)
		|| !check_vector(p[2], &(obj->cy.dir))
		|| !check_chkb(p[6], &obj->is_chkb))
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
