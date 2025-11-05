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
	printf("Error\n\n");
	if (code == INVALID_OPTION)
	{
		printf("Invalid bonus option: %s\n", s);
		printf("Format: key:value\n");
		printf("Supported keys: chkb | mat | alb\n");
	}
	else if (code == INVALID_CHKB)
	{
		printf("Invalid checkerboard value: %s\n", s);
		printf("Expected: true | false\n");
	}
	else if (code == INVALID_MAT)
	{
		printf("Invalid material: %s\n", s);
		printf("Supported keys: lambertian | metal\n");
	}
	else if (code == INVALID_ALBEDO)
	{
		printf("Albedo out of range: %s\n", s);
		printf("Accepted range: [0.0001, 1]\n");
	}
	else if (code == DUP_KEY)
		printf("Duplicate bonus option: %s\n", s);
}
