/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:27:49 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/20 18:50:13 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <stdlib.h>
#include <stdio.h>
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

static int		handle_key_event(int keycode, void *param)
{
	t_app	*app;

	app = (t_app*)param;
	(void)app;
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

static int		millis_since(struct timeval *start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return (1000 * (end.tv_sec - start->tv_sec)
		+ (end.tv_usec - start->tv_usec) / 1000);
}

static int		main_loop(t_app *app)
{
	int		to_sleep;

	if (!app->rendered)
	{
		usleep(30 * 1000);
		return (0);
	}
	to_sleep = 50 - millis_since(&(app->last_render));
	if (to_sleep > 0)
		usleep(to_sleep * 1000);
	mlx_put_image_to_window(app->mlx, app->win, app->image.ptr, 0, 0);
	gettimeofday(&(app->last_render), NULL);
	return (0);
}

void			*main_draw_loop(void *v_app)
{
	t_app		*app;

	app = (t_app *)v_app;
	if (app->rendered)
		return (0);
	gettimeofday(&(app->last_render), NULL);
	app->rendered = 1;
	start_threads(app, app->hitable_list);
	return (NULL);
}

int				main(int argc, char **argv)
{
	t_app		app;
	pthread_t	loop_thread;
	
	app.rendered = 0;
	pthread_mutex_init(&(app.mutex), NULL);
	app.mlx = mlx_init();
	app.win = mlx_new_window(app.mlx, WIN_WIDTH, WIN_HEIGHT, "RTv1");
	mlx_key_hook(app.win, handle_key_event, &app);
	mlx_expose_hook(app.win, main_loop, &app);
	app.image.ptr = mlx_new_image(app.mlx, WIN_WIDTH, WIN_HEIGHT);
	app.image.data = (int *)mlx_get_data_addr(app.image.ptr, app.image.infos,
			app.image.infos + 1, app.image.infos + 2);
	camera_init(&(app.camera));
	read_scene(&app, argc, argv);
	pthread_create(&loop_thread, NULL, main_draw_loop, &app);
	mlx_loop_hook(app.mlx, main_loop, &app);
	mlx_loop(app.mlx);
	return (0);
}
