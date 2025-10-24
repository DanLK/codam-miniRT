/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_fill_in_objects_bonus.c   	                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/03 16:22:22 by hogu          #+#    #+#                 */
/*   Updated: 2025/10/13 13:40:27 by dloustalot    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

/*get keys and values from bonus options*/
static bool	split_kv(const char *tok, char **key, char **val)
{
	const char	*eq;
	char		*tmp;

	if (!tok)
		return (false);
	eq = ft_strchr(tok, ':');
	if (!eq || eq == tok || *(eq + 1) == '\0')
		return (false);
	*key = ft_substr(tok, 0, eq - tok);
	*val = ft_substr(tok, (eq - tok) + 1, ft_strlen(tok) - (eq - tok) - 1);
	if (!*key || !*val)
		return (free(*key), free(*val), false);
	tmp = ft_strtrim(*key, " \t");
	free(*key);
	*key = tmp;
	tmp = ft_strtrim(*val, " \t");
	free(*val);
	*val = tmp;
	if (!*key || !*val || **key == '\0' || **val == '\0')
		return (free(*key), free(*val), false);
	return (true);
}

static bool	handle_option(const char *k, const char *v, t_object *obj)
{
	if (!ft_strcmp(k, "chkb"))
		return (check_chkb(v, &obj->is_chkb, obj));
	else if (!ft_strcmp(k, "mat"))
		return (check_mat_type(v, obj));
	else if (!ft_strcmp(k, "alb"))
		return (check_albedo(v, obj));
	else
		return (print_error_bonus(INVALID_OPTION, k), false);
}

static bool	parse_options(char **opt, t_object *obj)
{
	int		i;
	char	*k;
	char	*v;

	if (!opt || !obj)
		return (false);
	i = 0;
	k = NULL;
	v = NULL;
	while (opt[i])
	{
		if (!split_kv(opt[i], &k, &v))
			return (print_error_bonus(INVALID_OPTION, opt[i]), false);
		if (!handle_option(k, v, obj))
			return (free(k), free(v), false);
		free(k);
		free(v);
		i++;
	}
	return (true);
}

static void	finalize_object(t_object *obj)
{
	if (!obj)
		return ;
	if (obj->material.type == DEFAULT && obj->bonus_status.has_albedo)
		obj->material.type = LAMBERTIAN;
	if ((obj->material.type == LAMBERTIAN || obj->material.type == METAL)
		&& !obj->bonus_status.has_albedo)
		obj->material.albedo = obj->color;
}

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
	if (p[i_opt] && !parse_options(&p[i_opt], obj))
		return (free(obj), free_split(p), false);
	finalize_object(obj);
	append_object(&scene->objects, obj);
	return (free_split(p), true);
}
