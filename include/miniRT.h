/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 13:30:20 by hogu          #+#    #+#                 */
/*   Updated: 2025/08/07 15:12:18 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <float.h>

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
}	t_coord;

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_coord	pos;
	t_vec	dir;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_coord			pos;
	double			ratio;
	t_color			color;
}	t_light;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef struct s_object
{
	t_obj_type		type;
	void			*element;
	struct s_object	*next;
}	t_object;

typedef struct s_sphere
{
	t_coord	center;
	double	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_coord	point;
	t_vec	dir;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_coord	center;
	t_vec	dir;
	double	diameter;
	double	height;
	t_color	color;
}	t_cylinder;

typedef struct s_scene_status
{
	bool	has_ambient;
	bool	has_camera;
	bool	has_light;
	bool	has_sphere;
	bool	has_plane;
	bool	has_cylinder;
}	t_scene_status;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_object		*objects;
	t_scene_status	status;
}	t_scene;

typedef enum e_error_code
{
	WRONG_ARGS,
	WRONG_SUFFIX,
	EMPTY_FILE,
	PARAM_TYPE,
	PARAM_COUNT,
	DOUBLE,
	WRONG_ELEM_COUNT,
	OUT_RANGE,
	VEC_NORM,
	DIGITS_ONLY,
	DUP_ELEM,
	MISS_ELEM,
}	t_error_code;

# define EPSILON 1e-8

//---------------------Parser----------------------------
bool		parser(t_scene *scene, const char *filename);
void		print_scene(t_scene *scene);

//parser_ato
bool		ft_atod(const char *s, double *result);
bool		ft_atoi_strict(const char *s, int *result, int max_value);

//parser_check_input
bool		check_suffix(const char *str);
bool		check_color(const char *s, t_color *color);
bool		check_coord(const char *s, t_coord *pos);
bool		check_vector(const char *s, t_vec *v);
bool		check_ratio(const char *s, double *ratio_in_struct);

//parser_fill_in_structs
bool		fill_in_ambient(const char *line, t_scene *scene);
bool		fill_in_camera(const char *line, t_scene *scene);
bool		fill_in_light(const char *s, t_scene *scene);
bool		fill_in_sphere(const char *s, t_scene *scene);
bool		fill_in_plane(const char *s, t_scene *scene);
bool		fill_in_cylinder(const char *s, t_scene *scene);

//parser_space_split
void		free_split(char **split);
char		**space_split(char const *s);

//parser_util
bool		check_range(double value, double min, double max);
bool		check_equal(double value, double target);
const char	*skip_spaces(const char *s);
bool		ft_isspace(char c);
void		free_object_list(t_object *obj);

//print_error
void		print_error(int code, const char *s);

#endif