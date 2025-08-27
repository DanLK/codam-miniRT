/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_atod.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/11 15:49:38 by hogu          #+#    #+#                 */
/*   Updated: 2025/08/26 12:11:15 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	parse_sign(const char **s)
{
	if (**s == '-')
	{
		(*s)++;
		return (-1);
	}
	else if (**s == '+')
	{
		(*s)++;
		return (1);
	}
	return (1);
}

static bool	parse_uint_part(const char **s, double *accum, bool *has_digit)
{
	while ((**s) >= '0' && (**s) <= '9')
	{
		*has_digit = true;
		if (*accum > (DBL_MAX - (**s - '0')) / 10.0)
			return (false);
		*accum = *accum * 10.0 + (**s - '0');
		(*s)++;
	}
	return (true);
}

static void	parse_frac_part(const char **s, double *accum, bool *has_digit)
{
	double	factor;

	if (**s != '.')
		return ;
	(*s)++;
	factor = 0.1;
	while ((**s) >= '0' && (**s) <= '9')
	{
		*has_digit = true;
		*accum += (**s - '0') * factor;
		factor *= 0.1;
		(*s)++;
	}
}

bool	ft_atod(const char *s, double *result)
{
	const char	*p;
	int			sign;
	bool		has_digit;
	double		accum;

	if (!s || !result)
		return (false);
	has_digit = false;
	accum = 0.0;
	p = skip_spaces(s);
	sign = parse_sign(&p);
	if (!parse_uint_part(&p, &accum, &has_digit))
		return (false);
	parse_frac_part(&p, &accum, &has_digit);
	p = skip_spaces(p);
	if (!has_digit || *p != '\0')
		return (false);
	accum *= (double)sign;
	if (!isfinite(accum))
		return (false);
	*result = accum;
	return (true);
}

bool	ft_atoi_strict(const char *s, int *result, int max_value)
{
	const char	*p;
	long		val;

	if (!s || !result || max_value <= 0)
		return (false);
	p = skip_spaces(s);
	if (*p < '0' || *p > '9')
		return (print_error(DIGITS_ONLY, s), false);
	val = 0;
	while (*p >= '0' && *p <= '9')
	{
		val = val * 10 + (*p - '0');
		if (val > max_value)
			return (print_error(OUT_RANGE, s), false);
		p++;
	}
	p = skip_spaces(p);
	if (*p != '\0')
		return (print_error(DIGITS_ONLY, s), false);
	*result = (int)val;
	return (true);
}
