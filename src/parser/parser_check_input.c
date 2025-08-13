/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser_check_color.c                                :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/12 12:17:08 by hogu           #+#    #+#                */
/*   Updated: 2025/08/12 12:17:09 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

bool	check_suffix(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (!str || len < 3)
		return (false);
	return (ft_strncmp(str + len - 3, ".rt", 3) == 0);
}

bool	check_color(const char *s, t_color *color)
{
	char	**cl;
	int		r;
	int		g;
	int		b;

	cl = ft_split(s, ',');
	if (!cl || !cl[0] || !cl[1] || !cl[2] || cl[3])
		return (print_error(WRONG_ELEM_COUNT, s), free_split(cl), false);
	if (!ft_atoi_strict(cl[0], &r, 255) || !ft_atoi_strict(cl[1], &g, 255)
		|| !ft_atoi_strict(cl[2], &b, 255))
		return (free_split(cl), false);
	color->r = r;
	color->g = g;
	color->b = b;
	return (free_split(cl), true);
}

bool	check_coord(const char *s, t_coord *pos)
{
	char	**ps;
	double	x;
	double	y;
	double	z;

	ps = ft_split(s, ',');
	if (!ps || !ps[0] || !ps[1] || !ps[2] || ps[3])
		return (print_error(WRONG_ELEM_COUNT, s), free_split(ps), false);
	if (!ft_atod(ps[0], &x) || !ft_atod(ps[1], &y) || !ft_atod(ps[2], &z))
		return (print_error(DOUBLE, s), free_split(ps), false);
	pos->x = x;
	pos->y = y;
	pos->z = z;
	return (free_split(ps), true);
}

bool	check_vector(const char *s, t_vec *v)
{
	char	**vc;
	double	x;
	double	y;
	double	z;

	vc = ft_split(s, ',');
	if (!vc || !vc[0] || !vc[1] || !vc[2] || vc[3])
		return (print_error(WRONG_ELEM_COUNT, s), free_split(vc), false);
	if (!ft_atod(vc[0], &x) || !ft_atod(vc[1], &y) || !ft_atod(vc[2], &z))
		return (print_error(DOUBLE, s), free_split(vc), false);
	free_split(vc);
	if (!check_range(x, -1.0, 1.0) || !check_range(y, -1.0, 1.0)
		|| !check_range(z, -1.0, 1.0))
		return (print_error(OUT_RANGE, s), false);
	v->x = x;
	v->y = y;
	v->z = z;
	if (!check_equal(len_vec(v), 1.0))
		return (print_error(VEC_NORM, s), false);
	return (true);
}

bool	check_ratio(const char *s, double *ratio_in_struct)
{
	double	ratio;

	if (!s || !ft_atod(s, &ratio))
		return (print_error(DOUBLE, s), false);
	if (check_range(ratio, 0.0, 1.0))
	{
		*ratio_in_struct = ratio;
		return (true);
	}
	else
		return (print_error(OUT_RANGE, s), false);
}
