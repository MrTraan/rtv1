/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_primitives.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 10:41:01 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/24 16:12:17 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdio.h>

char		*parse_v3(char *data, t_v3 *v)
{
	int		matches;

	if ((matches = sscanf(data, "%*s %f %f %f\n",
			&(v->x), &(v->y), &(v->z))) != 3)
		return (parser_put_error("Invalid vector 3"));
	if (!(data = ft_strchr(data, '\n')))
		return (NULL);
	data++;
	return (data);
}

char		*parse_v3_radians(char *data, t_v3 *v)
{
	int		matches;

	if ((matches = sscanf(data, "%*s %f %f %f\n",
			&(v->x), &(v->y), &(v->z))) != 3)
		return (parser_put_error("Invalid vector 3"));
	v->x = TO_RADIAN(v->x);
	v->y = TO_RADIAN(v->y);
	v->z = TO_RADIAN(v->z);
	if (!(data = ft_strchr(data, '\n')))
		return (NULL);
	data++;
	return (data);
}

char		*parse_v3_unit(char *data, t_v3 *v)
{
	int		matches;
	t_v3	raw;

	if ((matches = sscanf(data, "%*s %f %f %f\n",
			&(raw.x), &(raw.y), &(raw.z))) != 3)
		return (parser_put_error("Invalid vector 3"));
	raw = v3_unit(raw);
	v->x = raw.x;
	v->y = raw.y;
	v->z = raw.z;
	if (!(data = ft_strchr(data, '\n')))
		return (NULL);
	data++;
	return (data);
}

char		*parse_float(char *data, float *f)
{
	int		matches;

	if ((matches = sscanf(data, "%*s %f\n", f)) != 1)
		return (parser_put_error("Invalid float"));
	if (!(data = ft_strchr(data, '\n')))
		return (NULL);
	data++;
	return (data);
}
