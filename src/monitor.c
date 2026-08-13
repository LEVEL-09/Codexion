/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:54:39 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/13 17:53:25 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor.h"
#include "coder.h"
#include "config.h"
#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static short	check_burnout(t_coder *coder, t_monitor *monitor)
{
	if (get_time_of_now(coder->config->start_time)
		>= coder->last_time_compile
		+ coder->config->time_to_burnout)
	{
		printf("%ld %d burned out\n",
			get_time_of_now(coder->config->start_time), coder->id);
		monitor->config->flag_burnout = true;
		pthread_cond_broadcast(&monitor->config->cond_burnout);
		return (1);
	}
	else if (coder->config->number_of_coders_completed
		== monitor->config->number_of_coders)
		return (1);
	return (0);
}

void	*monitor_check(void *monitor)
{
	int			i;
	t_coder		*coder;
	t_monitor	*now_monitor;

	i = 0;
	now_monitor = monitor;
	while (true)
	{
		if (i >= now_monitor->config->number_of_coders)
			i = 0;
		coder = now_monitor->coders[i++];
		pthread_mutex_lock(&now_monitor->config->mutex_burnout);
		if (check_burnout(coder, now_monitor))
			break ;
		pthread_mutex_unlock(&now_monitor->config->mutex_burnout);
	}
	pthread_mutex_unlock(&now_monitor->config->mutex_burnout);
	return (NULL);
}

t_monitor	*create_monitor(t_coder **coders, t_config *config)
{
	t_monitor		*monitor;

	monitor = malloc(sizeof(t_monitor));
	if (!monitor)
		return (NULL);
	monitor->coders = coders;
	monitor->config = config;
	return (monitor);
}
