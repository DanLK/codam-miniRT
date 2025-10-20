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

# define CHKB_COLS 3
# define CHKB_ROWS 3

//color_local_coord
void		set_local_basis(t_vec dir, t_basis *basis);
void		get_local_coord(t_basis *basis, t_coord *local, t_vec v);

//trace_color
// t_color		compute_color_lamb(t_ray ray, t_ray camera_ray, t_scene *scene, int depth);
bool		get_scattered_ray(t_ray ray, t_hit_point hp, t_ray *scattered, t_color *attenuation);
t_color		trace_color(t_ray ray, t_ray camera_ray, t_scene *scene, int depth);

//scattered
bool		get_scattered_lmb(t_ray ray, t_hit_point hp, t_ray *scatt, t_color *att);
bool		get_scattered_metal(t_ray ray, t_hit_point hp, t_ray *scatt, t_color *att);
// bool		get_scattered_default(t_ray ray, t_hit_point hp, t_ray *scatt, double *att);

//color_cal_checkerboard
t_color		cal_pl_chkb(t_object *obj, t_coord hit_p);
t_color		cal_sp_chkb(t_object *obj, t_coord hit_p);
t_color		cal_cy_chkb_cap(t_object *obj, t_vec v);
t_color		cal_cy_chkb_curved_surface(t_object *obj, t_vec v, double proj);

//parser
bool		check_chkb(const char *str, bool *is_chkb);
bool		check_material(const char *mat, const char *alb, t_material	*material);

//print error
void		print_error_bonus(int code, const char *s);

#endif
