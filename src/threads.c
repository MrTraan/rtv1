/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngrasset <ngrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 16:58:33 by ngrasset          #+#    #+#             */
/*   Updated: 2018/05/24 15:11:37 by ngrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <pthread.h>

void		compute_loop(t_thread_data *thread_data, t_iv2 point)
{
	t_v3			color;
	t_ray			r;
	float			u;
	float			v;
	int				i;

	color = (t_v3){0, 0, 0};
	i = 0;
	while (i < AA_ITER)
	{
		u = ((float)point.x + ft_rand() - 0.5f) / (float)WIN_WIDTH;
		v = ((WIN_HEIGHT - (float)point.y) + ft_rand() - 0.5f)
			/ (float)WIN_HEIGHT;
		r = camera_get_uv_ray(&(thread_data->app->camera), u, v);
		color = v3_add(color, compute_ray_color(thread_data->app,
					r, thread_data->hitable_list));
		i++;
	}
	color = v3_mul_float(color, 1.0f / AA_ITER);
	draw_pixel(thread_data->app, point, v3_to_color(color));
}

void		*compute_part(void *param)
{
	t_iv2			point;
	int				a;
	int				b;

	a = -1;
	while (++a < SKIP_N)
	{
		b = -1;
		while (++b < SKIP_N)
		{
			point.y = b;
			while (point.y < WIN_HEIGHT)
			{
				point.x = ((t_thread_data*)param)->start_x + a;
				while (point.x < ((t_thread_data*)param)->end_x)
				{
					compute_loop(param, point);
					point.x += SKIP_N;
				}
				point.y += SKIP_N;
			}
		}
	}
	return (NULL);
}

int			wait_for_threads_to_finish(pthread_t *threads)
{
	int		i;

	i = 0;
	while (i < NB_THREADS)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			ft_putstr("Error while waiting for thread\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int			start_threads(t_app *app, t_list *hitable_list)
{
	t_thread_data	threads_data[NB_THREADS];
	pthread_t		threads[NB_THREADS];
	int				i;

	i = 0;
	while (i < NB_THREADS)
	{
		threads_data[i] = (t_thread_data) {
			.app = app,
			.hitable_list = hitable_list,
			.start_x = i * WIN_WIDTH / NB_THREADS,
			.end_x = (i + 1) * WIN_WIDTH / NB_THREADS
		};
		if (pthread_create(&(threads[i]), NULL,
					compute_part, &(threads_data[i])) != 0)
		{
			ft_putstr_fd("Error while creating thread\n", 2);
			return (1);
		}
		i++;
	}
	return (wait_for_threads_to_finish(threads));
}
