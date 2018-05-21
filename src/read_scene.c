/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 15:57:53 by dbousque          #+#    #+#             */
/*   Updated: 2018/05/13 14:49:39 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
			ft_lstpush_back(&hitable_list, ft_lstnew(&s, sizeof(t_sphere)));
		}
		s.center.y = -2.5f;
		s.center.x += 0.7f;
	}

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

	t_cone cone = {
		.type = CONE,
		.origin = (t_v3){0.0f, .0f, -1.0f},
		.direction = v3_unit((t_v3){TO_RADIAN(45.f), TO_RADIAN(45.0f), TO_RADIAN(0.0f)}),
		.alpha = 10,
		.material = (t_material){
			.type = LAMBERTIAN,
			.color = (t_v3){.0f, 122.0f, .0f},
			.ambiant = .2f,
			.diffuse = .5f,
			.specular = .1f
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

void	scene_file_error(t_value *json, char *msg)
{
	free_value(json);
	ft_putstr("Invalid scene file : ");
	ft_putstr(msg);
	ft_putstr(", ignoring\n");
}

char	interpret_scene_object(t_app *app, t_value *object)
{
	char	*type;

	(void)app;
	type = (char*)(get_val(object, "type")->data);
	if (ft_strcmp(type, "plane") == 0)
	{

	}
	if (ft_strcmp(type, "cylinder") == 0)
	{

	}
	return (1);
}

void	interpret_scene_file(t_app *app, char *file_contents)
{
	t_value	*json;
	t_value	*object;
	int		i;

	json = read_json_str(file_contents);
	free(file_contents);
	if (json->type == 0)
		return (scene_file_error(json, "invalid JSON"));
	if (json->type != DICT)
		return (scene_file_error(json, "file is not a JSON object"));
	if (!(json = get_val(json, "objects")))
		return (scene_file_error(json, "missing objects field"));
	if (json->type != ARRAY)
		return (scene_file_error(json, "objects field is not an array"));
	i = 0;
	while ((object = get_tab(json)[i]))
	{
		if (!(get_val(object, "type")))
			return (scene_file_error(json, "missing type field in object"));
		if (get_val(object, "type")->type != STRING)
			return (scene_file_error(json, "type in object is not a string"));
		if (!(interpret_scene_object(app, object)))
			return (scene_file_error(json, "invalid object"));
		i++;
	}
	free_value(json);
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
