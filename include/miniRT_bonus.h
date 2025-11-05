/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT_bonus.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/08 15:51:36 by hogu          #+#    #+#                 */
/*   Updated: 2025/10/20 11:48:55 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "miniRT.h"

# define CHKB_COLS 5
# define CHKB_ROWS 5

//color_local_coord
void		set_local_basis(t_vec dir, t_basis *basis);
void		get_local_coord(t_basis *basis, t_coord *local, t_vec v);

//trace_color
bool		get_scattered_ray(t_ray ray, t_hit_point hp, t_ray *scattered,
				t_color *attenuation);
t_color		trace_color(t_ray ray, t_ray camera_ray, t_scene *scene, int depth);

//scattered
bool		get_scattered_lmb(t_ray ray, t_hit_point hp, t_ray *scatt,
				t_color *att);
bool		get_scattered_metal(t_ray ray, t_hit_point hp, t_ray *scatt,
				t_color *att);

//color_cal_checkerboard
t_color		cal_pl_chkb(t_hit_point *hp);
t_color		cal_sp_chkb(t_hit_point *hp);
t_color		cal_cy_chkb_cap(t_object *obj, t_vec v);
t_color		cal_cy_chkb_curved_surface(t_object *obj, t_vec v, double proj);

//parser
bool		check_chkb(const char *str, bool *is_chkb, t_object *obj);
bool		check_mat_type(const char *type, t_object *obj);
bool		check_albedo(const char *alb_num, t_object *obj);

//print error
void		print_error_bonus(int code, const char *s);

#endif
