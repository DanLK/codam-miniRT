/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interval.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/12 15:13:12 by dloustal      #+#    #+#                 */
/*   Updated: 2025/09/12 15:17:06 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	clamp(double *num, double min, double max)
{
	if (*num < min)
		*num = min;
	else if (*num > max)
		*num = max;
}