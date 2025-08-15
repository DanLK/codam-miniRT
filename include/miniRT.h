/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 13:30:20 by hogu          #+#    #+#                 */
/*   Updated: 2025/08/15 13:31:10 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIDTH 2048
# define RATIO (4.0 / 3.0)
# define HEIGHT (int)(WIDTH / RATIO)
# define EPSILON 1e-8
# include "libft.h"
# include "MLX42/MLX42.h"
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <float.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec	t_coord;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_ray
{
	t_coord	origin;
	t_vec	dir;
}		t_ray;

typedef struct s_vport
{
	double	width;
	double	height;
	double	distance;
	double	ratio;
	t_coord	center;
	t_vec	v_right;
	t_vec	v_down;
	t_vec	delta_x;
	t_vec	delta_y;
	t_coord	p_00;
}		t_vport;

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

//                 Vec
// Main
t_vec		*init_vec(double x, double y, double z);
t_vec		vec(double x, double y, double z);
void		neg_vec(t_vec *vec);
t_vec		neg_vec_new(t_vec vec);
void		scale_vec(t_vec *vec, double scalar);
t_vec		scaled(t_vec vec, double scalar);
double		len_vec(t_vec vec);
void		normalize(t_vec v);
t_vec		normalized(t_vec v);
// Operations
t_vec		sum_vec(t_vec u, t_vec v);
t_vec		*sum_vec_new(t_vec u, t_vec v);
double		dot(t_vec u, t_vec v);
t_vec		cross(t_vec u, t_vec v);
// Utils
void		print_vec(t_vec *v, char*name);

//                 Color
int			get_rgba(int r, int g, int b, int a);

//                 Rays
t_coord		ray_at(t_ray ray, double t);
t_vec		prim_ray_dir(t_camera cam, t_coord pixel);
t_ray		set_ray(t_camera cam, t_vec prim_ray_dir);

//viewport
void		make_vport(t_camera cam, t_vport *viewport);

//parser_ato
bool		ft_atod(const char *s, double *result);
bool		ft_atoi_strict(const char *s, int *result, int max_value);

//parser_check_input
bool		check_suffix(const char *str);
bool		check_color(const char *s, t_color *color);
bool		check_coord(const char *s, t_coord *pos);
bool		check_vector(const char *s, t_vec *v);

//parser_fill_in_structs
bool		fill_in_ambient(const char *line, t_scene *scene);
bool		fill_in_camera(const char *line, t_scene *scene);

//parser_space_split
void		free_split(char **split);
char		**space_split(char const *s);

//parser_util
bool		check_range(double value, double min, double max);
bool		check_equal(double value, double target);
const char	*skip_spaces(const char *s);

//print_error
void		print_error(int code, const char *s);

#endif