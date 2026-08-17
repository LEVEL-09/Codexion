/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:42:42 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/17 02:42:52 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "config.h"
#include "dongle.h"
#include "codexion.h"
#include "heap.h"
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

void	free_coders(t_coder **coders, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(coders[i]);
		i++;
	}
	free(coders);
}

t_coder	**create_coders(t_config *config)
{
	int			i;
	t_coder		**coders;

	i = 0;
	coders = malloc(sizeof(t_coder *) * config->number_of_coders);
	if (!coders)
		return (NULL);
	while (i < config->number_of_coders)
	{
		coders[i] = malloc(sizeof(t_coder));
		if (!coders[i])
		{
			free_coders(coders, i);
			return (NULL);
		}
		coders[i]->id = i + 1;
		coders[i]->last_time_compile = 0;
		coders[i]->numbers_of_compiles = 0;
		coders[i]->thread = 0;
		coders[i]->config = config;
		i++;
	}
	return (coders);
}

void	coder_compiling(void *coder)
{
	t_coder			*now_coder;

	now_coder = coder;
	if (coder_check_flag(now_coder))
		return (wakeup_coders_in_heap(now_coder, false));
	pthread_mutex_lock(&now_coder->left_dongle->mutex);
	pthread_mutex_lock(&now_coder->right_dongle->mutex);
	dongle_cooldown(coder, now_coder->left_dongle);
	dongle_cooldown(coder, now_coder->right_dongle);
	if (coder_check_flag(now_coder))
		return (wakeup_coders_in_heap(now_coder, true));
	printf("%ld %d has taken a dongle\n",
		get_time_of_now(now_coder->config->start_time), now_coder->id);
	printf("%ld %d has taken a dongle\n",
		get_time_of_now(now_coder->config->start_time), now_coder->id);
	pthread_mutex_lock(&now_coder->config->mutex_burnout);
	now_coder->last_time_compile
		= get_time_of_now(now_coder->config->start_time);
	pthread_mutex_unlock(&now_coder->config->mutex_burnout);
	printf("%ld %d is compiling\n",
		get_time_of_now(now_coder->config->start_time), now_coder->id);
	coder_sleeping(now_coder, now_coder->config->time_to_compile);
	release_dongles(now_coder);
}

void	coder_debugging(void *coder)
{
	t_coder			*now_coder;

	now_coder = coder;
	if (coder_check_flag(now_coder))
		return ;
	printf("%ld %d is debugging\n",
		get_time_of_now(now_coder->config->start_time), now_coder->id);
	coder_sleeping(now_coder, now_coder->config->time_to_debug);
}

void	coder_refactoring(void *coder)
{
	t_coder			*now_coder;

	now_coder = coder;
	if (coder_check_flag(now_coder))
		return ;
	printf("%ld %d is refactoring\n",
		get_time_of_now(now_coder->config->start_time), now_coder->id);
	coder_sleeping(now_coder, now_coder->config->time_to_refactor);
	return ;
}
