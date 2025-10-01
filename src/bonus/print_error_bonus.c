/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_error_bonus.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/03 16:42:52 by hogu          #+#    #+#                 */
/*   Updated: 2025/10/01 17:26:58 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	print_error_bonus(int code, const char *s)
{
	(void)s;
	printf("Error\n\n");
	if (code == INVALID_CHKB)
	{
		printf("Specify after object_color: True for checkerboard pattern, ");
		printf("False for pure color.\n");
	}
	if (code == INVALID_MAT)
	{
		printf("Invalid material or albedo after is_chkb\n");
		printf("Format: <mat:[material] alb:[albedo]>\n");
		printf("Possible materials:\n	-lambertian\n	-metal\n	-default\n");
		printf("Albedo must be in [0.0001,1]\n");
	}
}
