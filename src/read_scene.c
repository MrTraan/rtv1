/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 15:57:53 by dbousque          #+#    #+#             */
/*   Updated: 2018/05/22 12:43:16 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int str_is_whitespace(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\n')
		return (1);
	return (0);
}


void	set_default_scene(t_app *app)
{
	t_list	*hitable_list;

	hitable_list = NULL;
	t_sphere s = {
		.type = SPHERE,
		.center = (t_v3){-2.5f, -2.5f, .0f},
		.radius = .3f,
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){255.0f, .0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .9f
		}
	};

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			s.center.y += 0.7f;
			/* ft_lstpush_back(&hitable_list, ft_lstnew(&s, sizeof(t_sphere))); */
		}
		s.center.y = -2.5f;
		s.center.x += 0.7f;
	}
	
	t_sphere sl = {
		.type = SPHERE,
		.center = app->camera.light,
		.radius = .05f,
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){255.0f, .0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .9f
		}
	};
	ft_lstpush_back(&hitable_list, ft_lstnew(&sl, sizeof(t_sphere)));

	t_plane p = {
		.type = PLANE,
		.origin = (t_v3){.0f, .0f, -2.0f},
		.normal = (t_v3){.0f, .0f, 1.f},
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){122.0f, 122.0f, 122.0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .0f
		}
	};
	ft_lstpush_back(&hitable_list, ft_lstnew(&p, sizeof(t_plane)));
	(void)p;
	
	t_cylinder cylinder = {
		.type = CYLINDER,
		.origin = (t_v3){2.0f, .0f, -1.0f},
		.direction = (t_v3){.0f, 1.0f, .0f},
		.radius = .6f,
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){.0f, 122.0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .1f
		}
	};
	ft_lstpush_back(&hitable_list, ft_lstnew(&cylinder, sizeof(t_cylinder)));
	(void)cylinder;

	t_cone cone = {
		.type = CONE,
		.origin = (t_v3){0.0f, .0f, -1.0f},
		.direction = v3_unit((t_v3){0.5, 1, 0}),
		.alpha = TO_RADIAN(45),
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){.0f, 122.0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .9f
		}
	};
	ft_lstpush_back(&hitable_list, ft_lstnew(&cone, sizeof(t_cone)));

	app->hitable_list = hitable_list;
}

char	*read_error(char *error, char err, char *contents)
{
	if (contents)
		free(contents);
	*error = err;
	return (NULL);
}

char	*read_whole_file(char *filename, char *error, int max_size)
{
	char	*res;
	char	buf[1024];
	int		s;
	int		ret;
	int		fd;

	*error = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (read_error(error, 1, NULL));
	s = 0;
	while ((ret = read(fd, buf, 1024)) > 0)
	{
		s += ret;
		if (s > max_size)
			return (read_error(error, 3, NULL));
	}
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (read_error(error, 1, NULL));
	if (!(res = (char*)malloc(sizeof(char) * (s + 1))) || read(fd, res, s) < 0)
		return (read_error(error, 2, res));
	res[s] = '\0';
	return (res);
}
#include <stdio.h>
char		*parse_camera(t_app *app, char *data)
{
	t_v3	pos;
	t_v3	up;
	t_v3	lookat;
	t_v3 	light;
	int		matches;

	pos = CAM_DEFAULT_POS;
	up = CAM_DEFAULT_UP;
	lookat = CAM_DEFAULT_LOOKAT;
	light = CAM_DEFAULT_LIGHT;
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-pos ", data, 5) == 0)
		{
			if ((matches = sscanf(data, "-pos %f %f %f\n", &(pos.x), &(pos.y), &(pos.z))) != 3)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-up ", data, 4) == 0)
		{
			if ((matches = sscanf(data, "-up %f %f %f\n", &(up.x), &(up.y), &(up.z))) != 3)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-lookat ", data, 8) == 0)
		{
			if ((matches = sscanf(data, "-lookat %f %f %f\n", &(lookat.x), &(lookat.y), &(lookat.z))) != 3)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-light ", data, 7) == 0)
		{
			if ((matches = sscanf(data, "-light %f %f %f\n", &(light.x), &(light.y), &(light.z))) != 3)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else
			break ;
	}
	camera_init(&(app->camera), pos, up, lookat, light);
	return (data);
}

char	*parse_material(t_material *mat, char *data)
{
	int		matches;

	mat->type = LAMBERTIAN;
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-color ", data, 7) == 0)
		{
			if ((matches = sscanf(data, "-color %f %f %f\n", &(mat->color.x), &(mat->color.y), &(mat->color.z))) != 3)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-ambiant ", data, 9) == 0)
		{
			if ((matches = sscanf(data, "-ambiant %f\n", &(mat->ambiant))) != 1)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-diffuse ", data, 9) == 0)
		{
			if ((matches = sscanf(data, "-diffuse %f\n", &(mat->diffuse))) != 1)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-specular ", data, 10) == 0)
		{
			if ((matches = sscanf(data, "-specular %f\n", &(mat->specular))) != 1)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else
			break ;
	}
	return (data);

}

char	*parse_sphere(t_app *app, char *data)
{
	t_v3 	pos;
	float	radius;
	t_material mat;
	int		matches;
	t_sphere s;

	pos = SPHERE_DEFAULT_POS;
	radius = SPHERE_DEFAULT_RADIUS;
	mat = SPHERE_DEFAULT_MATERIAL;
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-pos ", data, 5) == 0)
		{
			if ((matches = sscanf(data, "-pos %f %f %f\n", &(pos.x), &(pos.y), &(pos.z))) != 3)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-radius ", data, 8) == 0)
		{
			if ((matches = sscanf(data, "-radius %f\n", &radius)) != 1)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-material\n", data, 10) == 0)
			data = parse_material(&mat, data + 10);
		else
			break ;
	}
	s = (t_sphere) { .type = SPHERE, .material = mat, .center = pos, .radius = radius };
	ft_lstpush_back(&(app->hitable_list), ft_lstnew(&s, sizeof(t_sphere)));
	return (data);
}

char	*parse_plane(t_app *app, char *data)
{
	t_v3 	pos;
	t_v3	normal;
	t_material mat;
	int matches;
	t_plane p;

	pos = PLANE_DEFAULT_POS;
	mat = PLANE_DEFAULT_MATERIAL;
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-pos ", data, 5) == 0)
		{
			if ((matches = sscanf(data, "-pos %f %f %f\n", &(pos.x), &(pos.y), &(pos.z))) != 3)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-normal ", data, 8) == 0)
		{
			if ((matches = sscanf(data, "-normal %f %f %f\n", &(normal.x), &(normal.y), &(normal.z))) != 3)
				break ;
			if (!(data = ft_strchr(data, '\n')))
				break ;
			data++;
		}
		else if (ft_strncmp("-material\n", data, 10) == 0)
			data = parse_material(&mat, data + 10);
		else
			break ;
	}
	p = (t_plane) { .type = PLANE, .material = mat, .origin = pos, .normal = normal };
	ft_lstpush_back(&(app->hitable_list), ft_lstnew(&p, sizeof(t_plane)));
	return (data);
}

void	interpret_scene_file(t_app *app, char *data)
{
	while (data && *data)
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("--camera\n", data, 9) == 0)
			data = parse_camera(app, data + 9);
		else if (ft_strncmp("--sphere\n", data, 9) == 0)
			data = parse_sphere(app, data + 9);
		else if (ft_strncmp("--plane\n", data, 8) == 0)
			data = parse_plane(app, data + 8);
		else
		{
			printf("Invalid instruction\n");
			data = ft_strchr(data, '\n');
			if (data)
				data++;
		}
	}
}

void	read_scene(t_app *app, int argc, char **argv)
{
	char	*file_contents;
	char	error;

	app->hitable_list = NULL;
	if (argc < 2)
	{
		ft_putstr("No scene to load\n");
		ft_putstr("Usage : ./rtv1 [scene_file]\n");
		set_default_scene(app);
		return ;
	}
	if (!(file_contents = read_whole_file(argv[1], &error, 3 * 1024 * 1024)))
	{
		if (error == 1)
			ft_putstr("Could not open scene file\n");
		if (error == 2)
			ft_putstr("Could not read scene file\n");
		if (error == 3)
			ft_putstr("Scene file is too big, must be <= 3MB\n");
		return ;
	}
	interpret_scene_file(app, file_contents);
}
