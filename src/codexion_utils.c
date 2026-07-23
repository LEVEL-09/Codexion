/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:33:13 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/10 18:08:19 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"
#include "config.h"
#include "dongle.h"
#include <sys/time.h>

void	sleep_even(t_coder *coder)
{
	if (coder->config->number_of_coders == 1)
		return ;
	if (coder->id % 2 == 0)
		coder_sleeping(coder, coder->config->time_to_compile);
	if (coder->config->number_of_coders % 2 != 0
		&& coder->id == coder->config->number_of_coders)
		coder_sleeping(coder, coder->config->time_to_compile * 2);
}

long	get_time_of_now(long start_time)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (result - start_time);
}

bool	coder_check_flag(t_coder *coder)
{
	bool	flag;

	pthread_mutex_lock(&coder->config->mutex_burnout);
	flag = coder->config->flag_burnout;
	pthread_mutex_unlock(&coder->config->mutex_burnout);
	return (flag);
}

void	dongle_cooldown(t_coder *coder, t_dongle *dongle)
{
	struct timespec	time;
	long			result;
	long			now;

	if (coder_check_flag(coder))
		return ;
	clock_gettime(CLOCK_REALTIME, &time);
	now = get_time_of_now(coder->config->start_time);
	pthread_mutex_lock(&coder->config->mutex_burnout);
	if (dongle->time_to_wait_dongle > now)
	{
		result = dongle->time_to_wait_dongle - now;
		time.tv_sec += result / 1000;
		time.tv_nsec += (result % 1000) * 1000000L;
		if (time.tv_nsec >= 1000000000L)
		{
			time.tv_sec += 1;
			time.tv_nsec -= 1000000000L;
		}
		pthread_cond_timedwait(&coder->config->cond_burnout,
			&coder->config->mutex_burnout, &time);
	}
	pthread_mutex_unlock(&coder->config->mutex_burnout);
	set_dongle_wait_time(coder, dongle);
}

void	coder_sleeping(t_coder *coder, long time_to_sleep)
{
	struct timespec	time;

	clock_gettime(CLOCK_REALTIME, &time);
	time.tv_sec += time_to_sleep / 1000;
	time.tv_nsec += (time_to_sleep % 1000) * 1000000L;
	pthread_mutex_lock(&coder->config->mutex_burnout);
	if (time.tv_nsec >= 1000000000L)
	{
		time.tv_sec += 1;
		time.tv_nsec -= 1000000000L;
	}
	pthread_cond_timedwait(&coder->config->cond_burnout,
		&coder->config->mutex_burnout, &time);
	pthread_mutex_unlock(&coder->config->mutex_burnout);
}
