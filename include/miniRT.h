/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/07 13:30:20 by hogu          #+#    #+#                 */
/*   Updated: 2025/08/11 14:28:51 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define WIDTH 1024
# define HEIGHT 512
# include "libft.h"
# include "MLX42/MLX42.h"
# include <unistd.h>
# include <math.h>
# include <stdio.h>

typedef struct s_cord
{
	double	x;
	double	y;
	double	z;
}	t_cord;

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
	t_cord	pos;
	t_vec	dir;
	double	fov;
}	t_camera;

typedef struct s_light
{
	t_cord			pos;
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

typedef struct s_object
{
	t_obj_type		type;
	void			*element;
	struct s_object	*next;
}	t_object;

typedef struct s_sphere
{
	t_cord	center;
	double	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_cord	point;
	t_vec	dir;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_cord	center;
	t_vec	dir;
	double	diameter;
	double	height;
	t_color	color;
}	t_cylinder;


typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}	t_scene;

//---------------------Vec----------------------------
// Main
t_vec	*init_vec(double x, double y, double z);
void	neg_vec(t_vec *vec);
void	scale_vec(t_vec *vec, double scalar);
double	len_vec(t_vec *vec);
void	normalize(t_vec *v);
// Operations
double	dot(t_vec *u, t_vec *v);
t_vec	*cross(t_vec *u, t_vec *v);
// Utils
void	print_vec(t_vec *v);

//--------------------COLOR---------------------------
int get_rgba(int r, int g, int b, int a);

#endif