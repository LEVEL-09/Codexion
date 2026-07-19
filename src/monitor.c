/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:54:39 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 05:31:12 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "coder.h"

void	*monitor_check(void *monitor)
{
	int			i;
	t_coder		*coder;
	t_monitor	*now_monitor;

	i = 0;
	now_monitor = monitor;
	while (true)
	{
		coder = now_monitor->coders[i % now_monitor->number_of_coder];
		pthread_mutex_lock(now_monitor->burn_out_mutex);
		if (get_time_of_now(coder->start_time)
			>= coder->last_time_compile + coder->time_to_burnout)
		{
			printf("%ld %d burned out\n",
				get_time_of_now(coder->start_time), coder->id);
			*now_monitor->flag_burnout = true;
			pthread_cond_broadcast(now_monitor->cond);
			pthread_mutex_unlock(now_monitor->burn_out_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(now_monitor->burn_out_mutex);
		i++;
	}
	return (NULL);
}

t_monitor	*create_monitor(t_coder **coders,
							pthread_mutex_t *mutex,
							pthread_cond_t *cond)
{
	t_monitor	*monitor;
	pthread_t	*thread;

	monitor = malloc(sizeof(t_monitor));
	thread = malloc(sizeof(pthread_t));
	monitor->thread = thread;
	monitor->coders = coders;
	monitor->burn_out_mutex = mutex;
	monitor->cond = cond;
	return (monitor);
}
