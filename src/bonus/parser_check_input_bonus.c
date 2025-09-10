/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_input_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:47:53 by hogu              #+#    #+#             */
/*   Updated: 2025/09/03 16:47:54 by hogu             ###   ########.fr       */
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
