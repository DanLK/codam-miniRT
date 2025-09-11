/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hogu <hogu@student.codam.nl>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 16:42:52 by hogu              #+#    #+#             */
/*   Updated: 2025/09/03 16:42:53 by hogu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	print_error_bonus(int code, const char *s)
{
	(void)s;
	printf("Error\n");
	if (code == INVALID_CHKB)
	{
		printf("Specify after object_color: True for checkerboard pattern, ");
		printf("False for pure color.\n");
	}
}
