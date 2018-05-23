/* ************************************************************************** */


/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:28:16 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/18 03:48:02 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

//TODO
//bug when light is at 0 0 0

# include <mlx.h>
# include <math.h>
# include <sys/time.h>
# include <libft.h>
# include <pthread.h>
# include <fcntl.h>

//remove
#include <stdio.h>

# define TO_RADIAN(x)	(x * M_PI/ 180)

# define CAMERA_THETA		20 * M_PI / 180
# define CAMERA_FOCUS_DIST	10
# define WIN_WIDTH		1200
# define WIN_HEIGHT		600
# define NB_THREADS		4
# define SKIP_N			4
# define SPECULAR_POW	50
# define AA_ITER		10

# define CAM_DEFAULT_POS ((t_v3){0.0f, 0.0f, 5.0f})
# define CAM_DEFAULT_LOOKAT ((t_v3){0.0f, 0.0f, 0.0f})
# define CAM_DEFAULT_UP ((t_v3){0.0f, 1.0f, 0.0f})
# define CAM_DEFAULT_LIGHT ((t_v3){-5.0, 5.0, 5.0})
# define CAM_DEFAULT_PARAMS ((t_camera_params) { \
		.pos = CAM_DEFAULT_POS, \
		.up = CAM_DEFAULT_UP, \
		.lookat = CAM_DEFAULT_LOOKAT, \
		.light = CAM_DEFAULT_LIGHT \
		})

# define SPHERE_DEFAULT_POS ((t_v3){0.0, 0.0, 0.0})
# define SPHERE_DEFAULT_RADIUS 0.3f
# define SPHERE_DEFAULT_MATERIAL ((t_material){ \
			.type = LAMBERTIAN, \
			.color = (t_v3){255.0f, .0f, .0f}, \
			.ambiant = .2f, \
			.diffuse = .5f, \
			.specular = .9f\
		})

# define PLANE_DEFAULT_POS ((t_v3){0.0, -2.0, 0.0})
# define PLANE_DEFAULT_NORMAL ((t_v3){0, 1, 0})
# define PLANE_DEFAULT_MATERIAL ((t_material){ \
			.type = LAMBERTIAN, \
			.color = (t_v3){122.0f, 122.0f, 122.0f}, \
			.ambiant = .2f, \
			.diffuse = .5f, \
			.specular = .0f\
		})

# define CYLINDER_DEFAULT_POS ((t_v3){-1.0, 0.0, 0.0})
# define CYLINDER_DEFAULT_DIRECTION ((t_v3){0, 0, 0})
# define CYLINDER_DEFAULT_RADIUS 0.6f
# define CYLINDER_DEFAULT_MATERIAL ((t_material){ \
			.type = LAMBERTIAN, \
			.color = (t_v3){0.0f, 122.0f, 122.0f}, \
			.ambiant = .2f, \
			.diffuse = .5f, \
			.specular = .0f\
		})

# define CONE_DEFAULT_POS ((t_v3){1.0, 0.0, 0.0})
# define CONE_DEFAULT_DIRECTION ((t_v3){0, 1, 0})
# define CONE_DEFAULT_ALPHA 45
# define CONE_DEFAULT_MATERIAL ((t_material){ \
			.type = LAMBERTIAN, \
			.color = (t_v3){122.0f, 0.0f, 122.0f}, \
			.ambiant = .2f, \
			.diffuse = .5f, \
			.specular = .6f\
		})

# define MAT_DEFAULT_AMBIANT 0.2
# define MAT_DEFAULT_DIFFUSE 0.5
# define MAT_DEFAULT_SPECULAR 0.3

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

# define LIGHT_COLOR ((t_v3){255.0f, 255.0f, 255.0f})

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
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
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

typedef struct		s_cylinder
{
	t_hitable_type	type;
	t_material		material;
	t_v3			origin;
	t_v3			direction;
	float			radius;
}					t_cylinder;

typedef struct		s_cone
{
	t_hitable_type	type;
	t_material		material;
	t_v3			origin;
	t_v3			direction;
	float			alpha;
}					t_cone;

typedef struct		s_plane
{
	t_hitable_type	type;
	t_material		material;
	t_v3			origin;
	t_v3			normal;
}					t_plane;

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
	t_list			*item_hit;
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

typedef struct		s_camera_params
{
	t_v3			pos;
	t_v3			up;
	t_v3			lookat;
	t_v3			light;
}					t_camera_params;

typedef struct		s_app
{
	void			*mlx;
	void			*win;
	t_image			image;
	t_camera		camera;
	char			rendered;
	struct timeval	last_render;
	t_list			*hitable_list;
	pthread_mutex_t	mutex;
}					t_app;

typedef struct		s_thread_data
{
	t_app			*app;
	t_list			*hitable_list;
	int				start_x;
	int				end_x;
}					t_thread_data;

void				camera_init(t_camera *cam, t_camera_params p);
t_ray				camera_get_ray(t_camera *cam, t_iv2 point);
t_ray				camera_get_uv_ray(t_camera *cam, float u, float v);

void				draw_pixel(t_app *app, t_iv2 point, int color);

int					start_threads(t_app *app, t_list *hitable_list);

t_v3				compute_ray_color(t_app *app, t_ray r, t_list *hitable_list);

t_v3				ray_point_at_parameter(t_ray r, float t);
char				ray_hit_sphere(t_sphere *sphere, t_ray r, t_v2 t_min_max,
						t_hit_record *rec);
char				ray_hit_plane(t_plane *plane, t_ray ray, t_v2 t_min_max,
						t_hit_record *rec);
char				ray_hit_cylinder(t_cylinder *cylinder, t_ray ray, t_v2 t_min_max, t_hit_record *rec);
char				ray_hit_cone(t_cone *cone, t_ray ray, t_v2 t_min_max, t_hit_record *rec);

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
t_v3				v3_rot_x(t_v3 src, float angle);
t_v3				v3_rot_y(t_v3 src, float angle);
t_v3				v3_rot_z(t_v3 src, float angle);
t_v3				v3_rot(t_v3 src, t_v3 rotation);

void				read_scene(t_app *app, int argc, char **argv);
char				*parse_v3(char *data, t_v3 *v);
char				*parse_v3_unit(char *data, t_v3 *v);
char				*parse_v3_radians(char *data, t_v3 *v);
char				*parse_float(char *data, float *f);
char				*read_error(char *error, char err, char *contents);
char				*parser_put_error(char *message);
char				*parser_put_invalid_instr(char *data);
int					str_is_whitespace(char *str);

char				*parse_cylinder(t_app *app, char *data);
char				*parse_plane(t_app *app, char *data);
char				*parse_sphere(t_app *app, char *data);
char				*parse_cone(t_app *app, char *data);
char				*parse_material(t_material *mat, char *data);

int					find_roots(t_v3 params, t_v2 min_max, float *res);

char				ray_hit(t_ray r, t_hitable *hitable, t_v2 boundaries, t_hit_record *rec);
char				ray_hit_list(t_ray r, t_list *hitable_list, t_v2 boundaries, t_hit_record *rec);

int					handle_key_event(int keycode, void *param);

#endif
