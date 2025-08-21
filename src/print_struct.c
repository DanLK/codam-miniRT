/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_struct.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/08/14 12:23:50 by hogu          #+#    #+#                 */
/*   Updated: 2025/08/21 15:54:26 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	print_color(t_color c)
{
	printf("  Color: (%d, %d, %d)\n", c.r, c.g, c.b);
}

void	print_coord(t_coord c)
{
	printf("  Coord: (%g, %g, %g)\n", c.x, c.y, c.z);
}

void	print_vector(t_vec v)
{
	printf("  Vector: (%g, %g, %g)\n", v.x, v.y, v.z);
}

void	print_ambient(t_ambient *a)
{
	printf("Ambient:\n");
	printf("  Ratio: %g\n", a->ratio);
	print_color(a->color);
	printf("\n");
}

void	print_camera(t_camera *c)
{
	printf("Camera:\n");
	print_coord(c->pos);
	print_vector(c->dir);
	printf("  FOV: %d\n", c->fov);
	printf("\n");
}

void	print_light(t_light *l)
{
	printf("Light:\n");
	print_coord(l->pos);
	printf("  Ratio: %g\n", l->ratio);
	print_color(l->color);
	printf("\n");
}

void	print_object(t_object *obj)
{
	while (obj)
	{
		if (obj->type == SPHERE)
		{
			t_sphere *s = (t_sphere *)obj->element;
			printf("Sphere:\n");
			print_coord(s->center);
			printf("  Diameter: %g\n", s->diameter);
			print_color(s->color);
			printf("\n");
		}
		else if (obj->type == PLANE)
		{
			t_plane *p = (t_plane *)obj->element;
			printf("Plane:\n");
			print_coord(p->point);
			print_vector(p->dir);
			print_color(p->color);
			printf("\n");
		}
		else if (obj->type == CYLINDER)
		{
			t_cylinder *c = (t_cylinder *)obj->element;
			printf("Cylinder:\n");
			print_coord(c->center);
			print_vector(c->dir);
			printf("  Diameter: %g\n", c->diameter);
			printf("  Height: %g\n", c->height);
			print_color(c->color);
			printf("\n");
		}
		obj = obj->next;
	}
}

void	print_scene(t_scene *scene)
{
	printf("====== Scene Info ======\n");
	print_ambient(&scene->ambient);
	print_camera(&scene->camera);
	print_light(&scene->light);
	print_object(scene->objects);
	printf("========================\n");
}

void	print_vport(t_vport *vp)
{
	printf("VP width: %f\n", vp->width);
	printf("VP height: %f\n", vp->height);
	printf("VP ratio: %f\n", vp->ratio);
	print_vec_name(&vp->center, "center");
	print_vec_name(&vp->v_right, "right");
	print_vec_name(&vp->v_down, "down");
	print_vec_name(&vp->p_00, "p(0,0)");
}