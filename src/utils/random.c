/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   random.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/11 15:58:52 by dloustal      #+#    #+#                 */
/*   Updated: 2025/09/12 15:25:14 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_rand	*init_rng()
{
	t_rand			*rng;
	struct timeval	tv;
	struct timezone	tz;
	uint64_t		seed;

	rng = malloc(sizeof(t_rand));
	if (!rng)
		return (NULL);
	// rng->increment = 127; // the fourth Mersenne prime
	gettimeofday(&tv, &tz); // For seeding
	seed = (uint64_t)tv.tv_sec * 1000000 + tv.tv_usec;
	rng->state = seed;
	rng->increment = (seed << 1) | 1;
	return (rng);
}

/* PCG random number generator*/
// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)
uint32_t	pcg_generator(t_rand	*rng)
{
	uint64_t	oldstate;
	uint32_t	xorshifted;
	uint32_t	rot;

	oldstate = rng->state;
	rng->state = oldstate * 6364136223846793005ULL + (rng->increment | 1);
	xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
	rot = oldstate >> 59u;
	return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

void	print_random_number()
{
	t_rand		*rng;
	uint32_t	number;

	rng = init_rng();
	if (!rng)
		return ;
	int i = 0;
	while (i++ < 10)
	{
		number = pcg_generator(rng);
		printf("Random number: %u\n", number);
	}
	free(rng);
}

double	random_double(void)
{
	double		n;
	t_rand		*rng;
	uint32_t	big_num;
	int			i;

	rng = init_rng();
	if (!rng)
		return (0); // Not sure what to do in this case
	i = 0;
	while (i++ < 5)
		big_num = pcg_generator(rng);
	n = ((double)big_num) / pow(2.0, 32.0);
	free(rng);
	return (n);
}

double	random_in(double min, double max)
{
	double	n;

	n = min + (max - min) * random_double();
	return (n);
}

void print_rand_double(void)
{
	printf("Random double: %f\n", random_double());
}

void print_rand_double_in(double min, double max)
{
	printf("Random double: %f\n", random_in(min, max));
}
