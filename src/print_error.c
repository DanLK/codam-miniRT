/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   print_error.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/07 15:50:10 by hogu           #+#    #+#                */
/*   Updated: 2025/08/07 15:50:11 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_error(int code, const char *s)
{
	printf("Error\n");
	if (code == WRONG_ARGS)
		printf("Proceed with one .rt file\n");
	else if (code == WRONG_SUFFIX)
		printf("Wrong suffix. Should be .rt\n");
	else if (code == EMPTY_FILE)
		printf("File is empty\n");
	else if (code == PARAM_TYPE)
		printf("Wrong parameter identifier: %s\n", s);
	else if (code == PARAM_COUNT)
		printf("Wrong number of parameter: %s\n", s);
	else if (code == DOUBLE)
		printf("Invalid number format: %s\n", s);
	else if (code == WRONG_ELEM_COUNT)
		printf("Three elements separated by comma: %s\n", s);
	else if (code == OUT_RANGE)
		printf("Number out of range: %s\n", s);
	else if (code == VEC_NORM)
		printf("Zero vector cannot be normalized: %s\n", s);
	else if (code == DIGITS_ONLY)
		printf("Only accepts non-negative integers in digits: %s\n", s);
	else if (code == DUP_ELEM)
		printf("Duplicate element: %s\n", s);
	else if (code == MISS_ELEM)
		printf("Missing element: %s\n", s);
}
