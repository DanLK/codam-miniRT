/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_check_input_bonus.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/03 16:47:53 by hogu          #+#    #+#                 */
/*   Updated: 2025/11/06 09:41:38 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

bool	check_chkb(const char *val, bool *is_chkb, t_object *obj)
{
	if (!val || !is_chkb)
		return (false);
	if (obj->bonus_status.has_chkb)
		return (print_error_bonus(DUP_KEY, "chkb"), false);
	if (!ft_strcmp(val, "true"))
		*is_chkb = true;
	else if (!ft_strcmp(val, "false"))
		*is_chkb = false;
	else
	{
		print_error_bonus(INVALID_CHKB, val);
		return (false);
	}
	obj->bonus_status.has_chkb = true;
	return (true);
}

bool	check_mat_type(const char *type, t_object *obj)
{
	if (!type)
		return (false);
	if (obj->bonus_status.has_mat)
		return (print_error_bonus(DUP_KEY, "mat"), false);
	if (!ft_strcmp(type, "lambertian"))
		obj->material.type = LAMBERTIAN;
	else if (!ft_strcmp(type, "metal"))
		obj->material.type = METAL;
	else
		return (print_error_bonus(INVALID_MAT, type), false);
	obj->bonus_status.has_mat = true;
	return (true);
}

bool	check_albedo(const char *alb_num, t_object *obj)
{
	double	albedo;

	if (!alb_num)
		return (false);
	if (obj->bonus_status.has_albedo)
		return (print_error_bonus(DUP_KEY, "albedo"), false);
	if (!ft_atod(alb_num, &albedo))
		return (print_error(DOUBLE, alb_num), false);
	if (albedo < 0.0001 || albedo > 1)
		return (print_error_bonus(INVALID_ALBEDO, alb_num), false);
	obj->material.albedo = col_scale(obj->color, albedo);
	obj->bonus_status.has_albedo = true;
	return (true);
}