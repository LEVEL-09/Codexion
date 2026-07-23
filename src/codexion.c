/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 15:10:57 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/10 18:54:11 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"
#include "heap.h"
#include "config.h"
#include "dongle.h"
#include "monitor.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static void	request_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	insert_heap(dongle->heap, coder);
	if (dongle->schedule == EDF && dongle->heap->size > 1)
		heapify(dongle->heap);
	while (dongle->heap->array[0]->id != coder->id)
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	extract_coder(dongle->heap);
	pthread_mutex_unlock(&dongle->mutex);
}

static void	get_dongles(t_coder *coder)
{
	t_dongle	*tmp;

	if (coder->config->number_of_coders == 1)
	{
		printf("%ld %d has taken a dongle\n",
			get_time_of_now(coder->config->start_time), coder->id);
		pthread_mutex_lock(&coder->config->mutex_burnout);
		pthread_cond_wait(&coder->config->cond_burnout,
			&coder->config->mutex_burnout);
		pthread_mutex_unlock(&coder->config->mutex_burnout);
		return ;
	}
	request_dongle(coder, coder->left_dongle);
	request_dongle(coder, coder->right_dongle);
	if (coder->left_dongle->id > coder->right_dongle->id)
	{
		tmp = coder->left_dongle;
		coder->left_dongle = coder->right_dongle;
		coder->right_dongle = tmp;
	}
	coder_compiling(coder);
	coder_debugging(coder);
	coder_refactoring(coder);
}

static void	*routine(void *coder)
{
	t_coder			*now_coder;

	now_coder = coder;
	sleep_even(now_coder);
	if (coder_check_flag(now_coder))
		return (NULL);
	while (true)
	{
		get_dongles(now_coder);
		pthread_mutex_lock(&now_coder->config->mutex_burnout);
		if (now_coder->config->flag_burnout)
		{
			pthread_mutex_unlock(&now_coder->config->mutex_burnout);
			return (NULL);
		}
		else if (now_coder->number_of_compiles_required <= 0)
		{
			now_coder->config->number_of_coders_completed++;
			now_coder->flag_complete = true;
			pthread_mutex_unlock(&now_coder->config->mutex_burnout);
			break ;
		}
		pthread_mutex_unlock(&now_coder->config->mutex_burnout);
	}
	return (NULL);
}

static int	run_threads(t_sim *sim)
{
	int	i;

	if (pthread_create(&sim->monitor->thread, NULL, monitor_check,
			sim->monitor) != 0)
	{
		fprintf(stderr, "Error: Failed to create monitor thread\n");
		return (0);
	}
	i = 0;
	while (i < sim->config->number_of_coders)
	{
		if (pthread_create(&sim->coders[i]->thread, NULL, routine,
				sim->coders[i]) != 0)
		{
			fprintf(stderr, "Error: Failed to create coder thread\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_sim	sim;

	if (!init_simulation(argc, argv, &sim))
		return (1);
	if (!run_threads(&sim))
	{
		destroy_everything(&sim, sim.config->number_of_coders);
		return (1);
	}
	join_and_cleanup(&sim);
	return (0);
}
