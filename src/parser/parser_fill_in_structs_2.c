/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser_fill_in_structs_2.c                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/13 12:27:58 by hogu           #+#    #+#                */
/*   Updated: 2025/08/13 12:27:59 by hogu           ########   odam.nl        */
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

static bool	alloc_obj_and_elem(t_object **obj, void **elem, size_t elem_size)
{
	*obj = (t_object *)malloc(sizeof(t_object));
	if (!*obj)
		return (printf("Error\n"), perror("malloc"), false);
	(*obj)->next = NULL;
	*elem = malloc(elem_size);
	if (!*elem)
		return (free(*obj), printf("Error\n"), perror("malloc"), false);
	return (true);
}

bool	fill_in_sphere(const char *s, t_scene *scene)
{
	char		**params;
	t_object	*obj;
	t_sphere	*sp;
	double		diameter;

	if (!s || !scene)
		return (false);
	params = space_split(s);
	if (!params || !params[1] || !params[2] || !params[3] || params[4])
		return (print_error(PARAM_COUNT, s), free_split(params), false);
	if (!alloc_obj_and_elem(&obj, (void **)&sp, sizeof(t_sphere)))
		return (free_split(params), false);
	if (!check_coord(params[1], &sp->center)
		|| !check_color(params[3], &sp->color))
		return (free(obj), free(sp), free_split(params), false);
	if (!ft_atod(params[2], &diameter))
		return (print_error(DOUBLE, params[2]), free(obj), free(sp),
			free_split(params), false);
	sp->diameter = diameter;
	obj->type = SPHERE;
	obj->element = (void *)sp;
	append_object(&scene->objects, obj);
	scene->status.has_sphere = true;
	return (free_split(params), true);
}

bool	fill_in_plane(const char *s, t_scene *scene)
{
	char		**params;
	t_object	*obj;
	t_plane		*pl;

	if (!s || !scene)
		return (false);
	params = space_split(s);
	if (!params || !params[1] || !params[2] || !params[3] || params[4])
		return (print_error(PARAM_COUNT, s), free_split(params), false);
	if (!alloc_obj_and_elem(&obj, (void **)&pl, sizeof(t_plane)))
		return (free_split(params), false);
	if (!check_coord(params[1], &pl->point)
		|| !check_vector(params[2], &pl->dir)
		|| !check_color(params[3], &pl->color))
		return (free(obj), free(pl), free_split(params), false);
	obj->type = PLANE;
	obj->element = (void *)pl;
	append_object(&scene->objects, obj);
	scene->status.has_plane = true;
	return (free_split(params), true);
}

bool	fill_in_cylinder(const char *s, t_scene *scene)
{
	char		**pr;
	t_object	*obj;
	t_cylinder	*cy;
	double		diameter;
	double		height;

	if (!s || !scene)
		return (false);
	pr = space_split(s);
	if (!pr || !pr[1] || !pr[2] || !pr[3] || !pr[4] || !pr[5] || pr[6])
		return (print_error(PARAM_COUNT, s), free_split(pr), false);
	if (!alloc_obj_and_elem(&obj, (void **)&cy, sizeof(t_cylinder)))
		return (free_split(pr), false);
	if (!check_coord(pr[1], &cy->center) || !check_vector(pr[2], &cy->dir)
		|| !check_color(pr[5], &cy->color))
		return (free(obj), free(cy), free_split(pr), false);
	if (!ft_atod(pr[3], &diameter) || !ft_atod(pr[4], &height))
		return (print_error(DOUBLE, "diameter or height"), free(obj),
			free(cy), free_split(pr), false);
	cy->diameter = diameter;
	cy->height = height;
	obj->type = CYLINDER;
	obj->element = (void *)cy;
	scene->status.has_cylinder = true;
	return (append_object(&scene->objects, obj), free_split(pr), true);
}
