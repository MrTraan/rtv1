/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:05:26 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/23 17:38:09 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		find_roots(t_v3 params, t_v2 min_max, float *res)
{
	float	discriminant;
	float	temp;

	discriminant = params.y * params.y - 4 * params.x * params.z;
	if (discriminant < 0)
		return (0);
	temp = ((-params.y - sqrt(discriminant)) / (2.0 * params.x));
	if (temp < min_max.x || temp > min_max.y)
		temp = ((-params.y + sqrt(discriminant)) / (2.0 * params.x));
	if (temp < min_max.x || temp > min_max.y)
		return (0);
	*res = temp;
	return (1);
}
