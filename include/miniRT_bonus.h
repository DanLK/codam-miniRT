/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT_bonus.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/09/08 15:51:36 by hogu          #+#    #+#                 */
/*   Updated: 2025/10/01 17:11:36 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "miniRT.h"

# define CHKB_COLS 10
# define CHKB_ROWS 10

//color_local_coord
void		set_local_basis(t_vec dir, t_basis *basis);
void		get_local_coord(t_basis *basis, t_coord *local, t_vec v);

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
