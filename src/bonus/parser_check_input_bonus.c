/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_check_input_bonus.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/03 16:47:53 by hogu          #+#    #+#                 */
/*   Updated: 2025/10/01 17:26:46 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

bool	check_chkb(const char *str, bool *is_chkb)
{
	if (ft_strncmp(str, "True", 4) == 0)
		*is_chkb = true;
	else if (ft_strncmp(str, "False", 5) == 0)
		*is_chkb = false;
	else
	{
		print_error_bonus(INVALID_CHKB, str);
		return (false);
	}
	return (true);
}

static bool	check_mat_type(const char *type, t_material *material)
{
	if (ft_strncmp(type, "lambertian", 10) == 0)
		material->type = LAMBERTIAN;
	else if (ft_strncmp(type, "metal", 5) == 0)
		material->type = METAL;
	else if (ft_strncmp(type, "default", 7) == 0)
		material->type = DEFAULT;
	else
		return (print_error_bonus(INVALID_MAT, type), false);
	return (true);
}

static bool	check_albedo(const char *alb_num, t_material *material)
{
	double albedo;

	if (!ft_atod(alb_num, &albedo))
		return (print_error_bonus(INVALID_MAT, alb_num), false);
	if (albedo < 0.0001 || albedo > 1)
		return (print_error_bonus(INVALID_MAT, alb_num), false);
	material->albedo = albedo;
	return (true);
}

bool	check_material(const char *mat, const char *alb, t_material	*material)
{
	char	*type;
	char	*alb_num;

	if (ft_strncmp(mat, "mat:", 4) == 0)
	{
		type = ft_substr(mat, 4, ft_strlen(mat) - 4);
		if (!type || !check_mat_type(type, material))
			return (free(type), false);
	}
	else
	{
		print_error_bonus(INVALID_MAT, mat);
		return (false);
	}
	if (ft_strncmp(alb, "alb:", 4) == 0)
	{
		alb_num = ft_substr(alb, 4, ft_strlen(alb) - 4);
		if (!alb_num || !check_albedo(alb_num, material))
			return (free(type), free(alb_num), false);
	}
	else
	{
		print_error_bonus(INVALID_MAT, mat);
		return (free(type), false);
	}
	return (free(type), free(alb_num), true);
}
