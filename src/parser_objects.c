/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:38:42 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/23 17:35:33 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

char	*parse_sphere(t_app *app, char *data)
{
	t_sphere	s;

	s.type = SPHERE;
	s.center = SPHERE_DEFAULT_POS;
	s.radius = SPHERE_DEFAULT_RADIUS;
	s.material = SPHERE_DEFAULT_MATERIAL;
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-pos ", data, 5) == 0)
			data = parse_v3(data, &(s.center));
		else if (ft_strncmp("-radius ", data, 8) == 0)
			data = parse_float(data, &(s.radius));
		else if (ft_strncmp("-material\n", data, 10) == 0)
			data = parse_material(&(s.material), data + 10);
		else
			break ;
	}
	ft_lstpush_back(&(app->hitable_list), ft_lstnew(&s, sizeof(t_sphere)));
	return (data);
}

char	*parse_plane(t_app *app, char *data)
{
	t_plane p;

	p.type = PLANE;
	p.origin = PLANE_DEFAULT_POS;
	p.material = PLANE_DEFAULT_MATERIAL;
	p.normal = PLANE_DEFAULT_NORMAL;
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-pos ", data, 5) == 0)
			data = parse_v3(data, &(p.origin));
		else if (ft_strncmp("-normal ", data, 8) == 0)
			data = parse_v3(data, &(p.normal));
		else if (ft_strncmp("-material\n", data, 10) == 0)
			data = parse_material(&(p.material), data + 10);
		else
			break ;
	}
	ft_lstpush_back(&(app->hitable_list), ft_lstnew(&p, sizeof(t_plane)));
	return (data);
}

char	*parse_cylinder(t_app *app, char *data)
{
	t_cylinder c;

	c.type = CYLINDER;
	c.origin = CYLINDER_DEFAULT_POS;
	c.material = CYLINDER_DEFAULT_MATERIAL;
	c.direction = CYLINDER_DEFAULT_DIRECTION;
	c.radius = CYLINDER_DEFAULT_RADIUS;
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-pos ", data, 5) == 0)
			data = parse_v3(data, &(c.origin));
		else if (ft_strncmp("-rotation ", data, 10) == 0)
			data = parse_v3_radians(data, &(c.direction));
		else if (ft_strncmp("-radius ", data, 8) == 0)
			data = parse_float(data, &(c.radius));
		else if (ft_strncmp("-material\n", data, 10) == 0)
			data = parse_material(&(c.material), data + 10);
		else
			break ;
	}
	ft_lstpush_back(&(app->hitable_list), ft_lstnew(&c, sizeof(t_cylinder)));
	return (data);
}

char	*parse_cone(t_app *app, char *data)
{
	t_cone c;

	c.type = CONE;
	c.material = CONE_DEFAULT_MATERIAL;
	c.origin = CONE_DEFAULT_POS;
	c.direction = CONE_DEFAULT_DIRECTION;
	c.alpha = CONE_DEFAULT_ALPHA;
	while (data && *data && data[1] != '-')
	{
		if (str_is_whitespace(data))
			data = ft_strchr(data, '\n') + 1;
		else if (ft_strncmp("-pos ", data, 5) == 0)
			data = parse_v3(data, &(c.origin));
		else if (ft_strncmp("-rotation ", data, 10) == 0)
			data = parse_v3_radians(data, &(c.direction));
		else if (ft_strncmp("-alpha ", data, 7) == 0)
			data = parse_float(data, &(c.alpha));
		else if (ft_strncmp("-material\n", data, 10) == 0)
			data = parse_material(&(c.material), data + 10);
		else
			break ;
	}
	c.direction = v3_unit(v3_rot(CONE_DEFAULT_DIRECTION, c.direction));
	ft_lstpush_back(&(app->hitable_list), ft_lstnew(&c, sizeof(t_cone)));
	return (data);
}
