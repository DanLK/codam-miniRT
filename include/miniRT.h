/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 13:30:20 by hogu          #+#    #+#                 */
/*   Updated: 2025/10/01 14:12:45 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIDTH 1536
# define RATIO (4.0 / 3.0)
# define HEIGHT (int)(WIDTH / RATIO)
# define EPSILON 1e-8
# define SAMPLES 3
# define DEPTH 2

# include "libft.h"
# include "MLX42/MLX42.h"
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <float.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec	t_coord;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
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
	struct s_light	*next;
}	t_light;

typedef enum e_obj_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_obj_type;

typedef	enum e_mat_type
{
	LAMBERTIAN,
	METAL,
	DEFAULT
}		t_mat_type;

typedef struct s_material
{
	double		albedo;
	t_mat_type	type;
}		t_material;

typedef struct s_sphere
{
	double	diameter;
}	t_sphere;

typedef struct s_basis
{
	t_vec	x_axis;
	t_vec	y_axis;
	bool	ready;
}	t_basis;

typedef struct s_plane
{
	t_vec	dir;
	t_basis	basis;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	dir;
	double	diameter;
	double	height;
	t_basis	basis;
}	t_cylinder;

typedef struct s_object
{
	t_obj_type		type;
	t_color			color;
	bool			is_chkb;
	t_color			show_color;
	t_coord			center;
	t_material		material;
	union
	{
		t_sphere	sp;
		t_cylinder	cy;
		t_plane		pl;
	};
	struct s_object	*next;
}	t_object;

typedef struct s_scene_status
{
	bool	has_ambient;
	bool	has_camera;
	bool	has_light;
}	t_scene_status;

typedef struct s_scene
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			*light;
	t_object		*objects;
	t_scene_status	status;
}	t_scene;

typedef struct s_rand
{
	uint64_t	state;
	uint64_t	increment;
}		t_rand;


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
	INVALID_CHKB
}	t_error_code;

typedef enum e_cy_position
{
	TOP_CAP,
	BOTTOM_CAP,
	WALL
}	t_cy_position;

//-----------------Vec------------------
t_vec		vec(double x, double y, double z);
double		len_vec(t_vec vec);
t_vec		neg_vec(t_vec vec);
t_vec		scaled(t_vec vec, double scalar);
t_vec		normalized(t_vec v);
// Operations
t_vec		sum_vec(t_vec u, t_vec v);
double		dot(t_vec u, t_vec v);
t_vec		cross(t_vec u, t_vec v);
t_vec		sub_vec(t_vec u, t_vec v);
t_vec		reject(t_vec v, t_vec dir);

//------------------------Utils-------------------------
// Random
t_rand		*init_rng();
uint32_t	pcg_generator(t_rand	*rng);
void		print_random_number();
double		random_double(void);
double		random_in(double min, double max);
void 		print_rand_double(void);
void 		print_rand_double_in(double min, double max);
//Random vec
t_vec		random_vec(void);
t_vec		random_vec_in(double min, double max);
t_vec		random_unit_vec(void);
t_vec		random_vec_on_hemis(t_vec normal);
//Interval
void		clamp(double *num, double min, double max); // Not using this function yet

//---------------------Parser----------------------------
bool		parser(t_scene *scene, const char *filename);

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
bool		validate_elem(t_scene *scene);
bool		fill_in_ambient(const char *line, t_scene *scene);
bool		fill_in_camera(const char *line, t_scene *scene);
bool		fill_in_light(const char *s, t_scene *scene);
bool		fill_in_sphere(const char *s, t_scene *scene);
bool		fill_in_plane(const char *s, t_scene *scene);
bool		fill_in_cylinder(const char *s, t_scene *scene);

//parser_list_manager
void		append_light(t_light **list, t_light *new);
void		append_object(t_object **list, t_object *new);
void		free_light_list(t_light *light);
void		free_object_list(t_object *obj);

//parser_space_split
char		**space_split(char const *s);

//parser_util
bool		check_range(double value, double min, double max);
bool		check_equal(double value, double target);
const char	*skip_spaces(const char *s);
void		free_split(char **split);
void		free_scene(t_scene *scene);

//print_error
void		print_error(int code, const char *s);

//-----------------for Debug------------------
void		print_scene(t_scene *scene);
void		print_vport(t_vport *vp);

//-----------------Event------------------
void		esc_hook(mlx_key_data_t keydata, void *param);
void		close_hook(void *param);

//-----------------Color------------------
t_color		calc_obj_color(t_object *obj, t_scene *scene, t_ray ray, double t);

//color_cal_lights
t_color		calc_obj_solo(t_color obj, t_color light, double ratio,
				double intens);
t_color		cal_diffuse(t_scene *scn, t_coord hit_p, t_object *obj,
				bool *in_shadow);

//color_intensity
t_vec		get_sphere_normal(t_object *obj, t_coord hit_p);
int			find_point_on_cylinder(t_object *obj, t_coord hit_p, t_vec *v,
				double *proj);
double		calc_intensity(t_coord hit_p, t_object *obj, t_coord light_p);
t_vec		get_normal(t_object *obj, t_coord hit_point);

//color_utils
int			get_rgba(t_color col, double alpha);
// t_color		sum_col_notinrange(t_color cl1, t_color cl2);
t_color		multiply_color(t_color cl1, t_color cl2);
t_color		sum_color(t_color cl1, t_color cl2);
t_color		calc_background_color(t_ray ray);
t_color		color(double r, double g, double b);
t_color		scale_col(t_color cl, double scalar);

//-----------------Viewport------------------
void		make_vport(t_camera cam, t_vport *viewport);

//-----------------Rays------------------
t_coord		ray_at(t_ray ray, double t);
t_ray		set_ray(t_coord start, t_vec ray_dir);

//-----------------Render------------------
void		render(mlx_image_t *img, t_scene *scene, t_vport *vp);
void		render_anti_aliasing(mlx_image_t *img, t_scene *scene, t_vport *vp);
t_ray		get_ray(int w, int h, t_vport *vp, t_scene *scene);
t_vec		sample_square(void);
void		render_aa_deep(mlx_image_t *img, t_scene *scene, t_vport *vp);
t_color		get_color_deep(t_ray ray, t_ray ray2, t_scene *scene, int depth);

//-----------------Hitting------------------
bool		hit_sphere(t_object *obj, t_ray ray, double *dist);
bool		hit_plane(t_object *obj, t_ray ray, double *dist);
bool		hit_cylinder(t_object *obj, t_ray ray, double *dist);
bool		hit_object(t_ray ray, t_object *obj, double *dist);
//cylinder
bool		hit_wall(t_object *obj, t_ray ray, double *dist);
bool		hit_cap(t_object *obj, t_ray ray, double *dist, char cap);

#endif