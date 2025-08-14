/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vec_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 16:44:19 by dloustal      #+#    #+#                 */
/*   Updated: 2025/08/14 16:49:35 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "stdio.h"

void	print_vec(t_vec *v, char*name)
{
	printf("%s: (%f, %f, %f)\n", name, v->x, v->y, v->z);
}