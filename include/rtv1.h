/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:28:16 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/17 19:16:33 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <mlx.h>
# include <math.h>
# include <sys/time.h>
# include <libft.h>

# define TO_RADIAN(x)	(x * M_PI/ 180)

# define CAMERA_THETA		20 * M_PI / 180
# define CAMERA_FOCUS_DIST	10
# define WIN_WIDTH		1200
# define WIN_HEIGHT		600
# define NB_THREADS		4
# define SKIP_N			4
# define SPECULAR_POW	50

typedef struct		s_iv2
{
	int				x;
	int				y;
}					t_iv2;

typedef struct		s_v2
{
	float			x;
	float			y;
}					t_v2;

typedef struct		s_v3
{
	float			x;
	float			y;
	float			z;
}					t_v3;

typedef enum		e_material_type
{
	LAMBERTIAN
}					t_material_type;

typedef struct		s_material
{
	t_material_type	type;
	t_v3			color;
	float			ambiant;
	float			diffuse;
	float			specular;
}					t_material;

typedef enum		e_hitable_type
{
	SPHERE
}					t_hitable_type;

typedef struct		s_hitable
{
	t_hitable_type	type;
	t_material		material;
}					t_hitable;

typedef struct		s_sphere
{
	t_hitable_type	type;
	t_material		material;
	t_v3			center;
	float			radius;
}					t_sphere;

typedef struct		s_ray
{
	t_v3			origin;
	t_v3			direction;
}					t_ray;

typedef struct		s_hit_record
{
	float			t;
	t_v3			p;
	t_v3			normal;
	t_material		material;
}					t_hit_record;

typedef struct		s_image
{
	void			*ptr;
	int				*data;
	int				infos[3];
}					t_image;

typedef struct		s_camera
{
	t_v3			origin;
	t_v3			lower_left_corner;
	t_v3			horizontal;
	t_v3			vertical;
	t_v3			u;
	t_v3			v;
	t_v3			w;
	t_v3			lookfrom;
	t_v3			lookat;
	t_v3			up;
	t_v3			light;
}					t_camera;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_camera		camera;
	char			rendered;
	struct timeval	last_render;
}					t_app;

typedef struct		s_thread_data
{
	t_app			*app;
	t_list			*hitable_list;
	int				start_x;
	int				end_x;
}					t_thread_data;

void				camera_init(t_camera *cam);
t_ray				camera_get_ray(t_camera *cam, t_iv2 point);

void				draw_pixel(t_app *app, t_iv2 point, int color);

int					start_threads(t_app *app, t_list *hitable_list);

t_v3				compute_ray_color(t_app *app, t_ray r, t_list *hitable_list);

void				v3_print(t_v3 v, char *msg);
t_v3				v3_add(t_v3 a, t_v3 b);
t_v3				v3_mul(t_v3 a, t_v3 b);
t_v3				v3_divide(t_v3 a, t_v3 b);
t_v3				v3_sub(t_v3 a, t_v3 b);
t_v3				v3_mul_float(t_v3 a, float f);
t_v3				v3_add_float(t_v3 a, float f);
t_v3				v3_unit(t_v3 src);
t_v3				v3_cross(t_v3 a, t_v3 b);
int					v3_to_color(t_v3 v);
float				v3_length(t_v3 v);
float				v3_dot(t_v3 a, t_v3 b);
t_v3				v3_reverse(t_v3 src);
float				v3_squared_length(t_v3 v);

#endif
