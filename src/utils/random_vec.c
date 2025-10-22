/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random_vec.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/15 11:41:39 by dloustal      #+#    #+#                 */
/*   Updated: 2025/10/22 15:12:41 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	random_vec(void)
{
	t_vec	random_vec;

	random_vec = vec(random_double(), random_double(), random_double());
	return (random_vec);
}

t_vec	random_vec_in(double min, double max)
{
	t_vec	random_vec;

	random_vec = vec(random_in(min, max), random_in(min, max), random_in(min, max));
	return (random_vec);
}

t_vec	random_unit_vec(void)
{
	t_vec	vec;
	double	len_sq;

	while (true)
	{
		vec = random_vec_in(-1.0, 1.0);
		len_sq = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
		if (len_sq <= 1.0 && EPSILON < len_sq)
		{
			// printf("(%f, %f, %f)\n", normalized(vec).x, normalized(vec).y, normalized(vec).z);
			return (normalized(vec));
		}
	}
}

/*Generates a random unit vector in the same hemisphere as the given normal*/
t_vec	random_vec_on_hemis(t_vec normal)
{
	t_vec	vec;

	vec = random_unit_vec();
	if (dot(vec, normal) >  0.0)
		return (vec);
	else
		return (neg_vec(vec));
}
