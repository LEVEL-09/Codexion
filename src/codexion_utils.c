/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:33:13 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 05:57:56 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"
#include "dongle.h"

long	get_time_of_now(long start_time)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (result - start_time);
}

void	dongle_cooldown(t_coder *coder, t_dongle *dongle)
{
	struct timespec	time;
	long			result;

	clock_gettime(CLOCK_REALTIME, &time);
	if (dongle->time_to_wait_dongle > get_time_of_now(coder->start_time))
	{
		result = (dongle->time_to_wait_dongle - get_time_of_now(coder->start_time));
		time.tv_sec += result / 1000;
		pthread_mutex_lock(coder->burn_out_mutex);
		pthread_cond_timedwait(coder->cond_of_monitor,
			coder->burn_out_mutex, &time);
		pthread_mutex_unlock(coder->burn_out_mutex);
	}
}

void	coder_sleeping(t_coder *coder)
{
	struct timespec	time;

	clock_gettime(CLOCK_REALTIME, &time);
	time.tv_sec += coder->time_to_compile / 1000;
	pthread_mutex_lock(coder->burn_out_mutex);
	pthread_cond_timedwait(coder->cond_of_monitor,
		coder->burn_out_mutex, &time);
	pthread_mutex_unlock(coder->burn_out_mutex);
}
