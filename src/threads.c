/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:58:33 by ngrasset          #+#    #+#             */
/*   Updated: 2018/04/17 17:39:10 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <pthread.h>

void		*compute_part(void *param)
{
	t_thread_data	*thread_data;
	t_iv2			point;
	t_ray			r;
	t_v3			color;

	thread_data = (t_thread_data*)param;
	for (int a = 0; a < SKIP_N; a++)
	{
		for (int b = 0; b < SKIP_N; b++)
		{
			for (point.y = b; point.y < WIN_HEIGHT; point.y+=SKIP_N) {
				for (point.x = thread_data->start_x + a; point.x < thread_data->end_x; point.x+=SKIP_N) {
					r = camera_get_ray(&(thread_data->app->camera), point);
					color = compute_ray_color(thread_data->app, r, thread_data->hitable_list);
					draw_pixel(thread_data->app, point, v3_to_color(color));
				}
			}
		}
	}
	return (NULL);
}

int			start_threads(t_app *app, t_list *hitable_list)
{
	t_thread_data	threads_data[NB_THREADS];
	pthread_t		threads[NB_THREADS];

	for (int i = 0; i < NB_THREADS; i++)
	{
		threads_data[i] = (t_thread_data) {
			.app = app,
			.hitable_list = hitable_list,
			.start_x = i * WIN_WIDTH / NB_THREADS,
			.end_x = (i + 1) * WIN_WIDTH / NB_THREADS
		};
		if (pthread_create(&(threads[i]), NULL, compute_part, &(threads_data[i])) != 0)
		{
			ft_putstr("Error while creating thread\n");
			return (1);
		}
	}
	for (int i = 0; i < NB_THREADS; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			ft_putstr("Error while waiting for thread\n");
			return (1);
		}
	}
	return (0);
}
