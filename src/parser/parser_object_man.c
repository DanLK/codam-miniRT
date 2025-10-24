/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_objects.c		                            :+:    :+:            */
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
	(*obj)->material.type = DEFAULT;
	(*obj)->material.albedo = color(1.0, 1.0, 1.0);
	(*obj)->is_chkb = false;
	(*obj)->next = NULL;
	return (true);
}

bool	parse_sphere_man(char **p, t_object **out, int *i_opt)
{
	t_object	*obj;
	double		diameter;

	if (!p || !p[1] || !p[2] || !p[3])
		return (print_error(PARAM_COUNT, "sp"), false);
	if (!alloc_object(&obj))
		return (false);
	if (!check_coord(p[1], &obj->center) || !check_color(p[3], &obj->color))
		return (free(obj), false);
	if (!ft_atod(p[2], &diameter))
		return (print_error(DOUBLE, p[2]), free(obj), false);
	if (diameter <= 0.0)
		return (print_error(OUT_RANGE, p[2]), free(obj), false);
	obj->sp.diameter = diameter;
	obj->type = SPHERE;
	*out = obj;
	if (i_opt)
		*i_opt = 4;
	return (true);
}

bool	parse_plane_man(char **p, t_object **out, int *i_opt)
{
	t_object	*obj;

	if (!p || !p[1] || !p[2] || !p[3])
		return (print_error(PARAM_COUNT, "pl"), false);
	if (!alloc_object(&obj))
		return (false);
	if (!check_coord(p[1], &obj->center) || !check_vector(p[2], &(obj->pl.dir))
		|| !check_color(p[3], &obj->color))
		return (free(obj), false);
	obj->type = PLANE;
	*out = obj;
	if (i_opt)
		*i_opt = 4;
	return (true);
}

bool	parse_cylinder_man(char **p, t_object **out, int *i_opt)
{
	t_object	*obj;
	double		diameter;
	double		height;

	if (!p || !p[1] || !p[2] || !p[3] || !p[4] || !p[5])
		return (print_error(PARAM_COUNT, "cy"), false);
	if (!alloc_object(&obj))
		return (false);
	if (!check_coord(p[1], &obj->center) || !check_color(p[5], &obj->color)
		|| !check_vector(p[2], &(obj->cy.dir)))
		return (free(obj), false);
	if (!ft_atod(p[3], &diameter) || !ft_atod(p[4], &height))
		return (print_error(DOUBLE, "cy:d/h"), free(obj), false);
	if (diameter < 0 || height < 0)
		return (print_error(OUT_RANGE, "cy:d/h"), free(obj), false);
	obj->cy.diameter = diameter;
	obj->cy.height = height;
	obj->type = CYLINDER;
	*out = obj;
	if (i_opt)
		*i_opt = 6;
	return (true);
}
