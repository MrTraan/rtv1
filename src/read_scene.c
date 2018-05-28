/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbousque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 15:57:53 by dbousque          #+#    #+#             */
/*   Updated: 2018/05/28 09:44:52 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*read_whole_file(char *filename, char *error, int max_size)
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

char		*parse_camera(t_app *app, char *data)
{
	t_camera_params		p;

	p = cam_default_params();
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-pos ", data, 5) == 0)
			data = parse_v3(data, &(p.pos));
		else if (ft_strncmp("-up ", data, 4) == 0)
			data = parse_v3(data, &(p.up));
		else if (ft_strncmp("-lookat ", data, 8) == 0)
			data = parse_v3(data, &(p.lookat));
		else if (ft_strncmp("-light ", data, 7) == 0)
			data = parse_v3(data, &(p.light));
		else
			break ;
	}
	camera_init(&(app->camera), p);
	return (data);
}

char		*parse_material(t_material *mat, char *data)
{
	mat->type = LAMBERTIAN;
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-color ", data, 7) == 0)
			data = parse_v3(data, &(mat->color));
		else if (ft_strncmp("-ambiant ", data, 9) == 0)
			data = parse_float(data, &(mat->ambiant));
		else if (ft_strncmp("-diffuse ", data, 9) == 0)
			data = parse_float(data, &(mat->diffuse));
		else if (ft_strncmp("-specular ", data, 10) == 0)
			data = parse_float(data, &(mat->specular));
		else
			break ;
	}
	return (data);
}

void		interpret_scene_file(t_app *app, char *data)
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
		else if (ft_strncmp("--cylinder\n", data, 11) == 0)
			data = parse_cylinder(app, data + 11);
		else if (ft_strncmp("--cone\n", data, 7) == 0)
			data = parse_cone(app, data + 7);
		else
		{
			parser_put_invalid_instr(data);
			data = ft_strchr(data, '\n');
			if (data)
				data++;
		}
	}
}

int			read_scene(t_app *app, int argc, char **argv)
{
	char	*file_contents;
	char	error;

	app->hitable_list = NULL;
	if (argc < 2)
	{
		ft_putstr("No scene to load\n");
		ft_putstr("Usage : ./rtv1 [scene_file]\n");
		return (1);
	}
	if (!(file_contents = read_whole_file(argv[1], &error, 3 * 1024 * 1024)))
	{
		if (error == 1)
			ft_putstr("Could not open scene file\n");
		if (error == 2)
			ft_putstr("Could not read scene file\n");
		if (error == 3)
			ft_putstr("Scene file is too big, must be <= 3MB\n");
		return (1);
	}
	interpret_scene_file(app, file_contents);
	return (0);
}
