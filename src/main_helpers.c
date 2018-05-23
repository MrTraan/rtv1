/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 17:33:00 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/23 17:33:54 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		draw_pixel(t_app *app, t_iv2 point, int color)
{
	pthread_mutex_lock(&(app->mutex));
	*(app->image.data + (point.x + (WIN_WIDTH * point.y))) =
		(int)mlx_get_color_value(app->mlx, color);
	pthread_mutex_unlock(&(app->mutex));
}

void		delete_itable(void *hitable, size_t size)
{
	(void)size;
	free(hitable);
}

int			handle_key_event(int keycode, void *param)
{
	t_app	*app;

	app = (t_app*)param;
	if (keycode == 53 || keycode == 65307)
	{
		pthread_mutex_lock(&(app->mutex));
		mlx_destroy_image(app->mlx, app->image.ptr);
		mlx_destroy_window(app->mlx, app->win);
		ft_lstdel(&(app->hitable_list), delete_itable);
		exit(1);
	}
	return (0);
}
