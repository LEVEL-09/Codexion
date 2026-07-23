/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:38:38 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/10 18:09:07 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongle.h"
#include "codexion.h"
#include "coder.h"
#include "heap.h"
#include "config.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

void	set_dongle_wait_time(t_coder *coder, t_dongle *dongle)
{
	long	now;

	now = get_time_of_now(coder->config->start_time);
	dongle->time_to_wait_dongle = now + dongle->cooldown
		+ coder->config->time_to_compile;
}

short	get_schedule(char *argv[])
{
	if (!strcmp(argv[8], "edf"))
		return (EDF);
	return (FIFO);
}

void	free_dongles(t_dongle **dongles, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&dongles[i]->mutex);
		pthread_cond_destroy(&dongles[i]->cond);
		free(dongles[i]->heap->array);
		free(dongles[i]->heap);
		free(dongles[i]);
		i++;
	}
	free(dongles);
}

static int	init_dongle(t_dongle *dongle, int id, char *argv[])
{
	dongle->id = id;
	dongle->cooldown = ft_atoi(argv[7]);
	dongle->time_to_wait_dongle = 0;
	dongle->schedule = get_schedule(argv);
	pthread_mutex_init(&dongle->mutex, NULL);
	pthread_cond_init(&dongle->cond, NULL);
	dongle->heap = create_heap(2);
	if (!dongle->heap)
		return (0);
	return (1);
}

t_dongle	**create_dongles(int number_of_dongle, char *argv[])
{
	int			i;
	t_dongle	**dongles;

	dongles = malloc(sizeof(t_dongle *) * number_of_dongle);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < number_of_dongle)
	{
		dongles[i] = malloc(sizeof(t_dongle));
		if (!dongles[i] || !init_dongle(dongles[i], i + 1, argv))
		{
			free(dongles[i]);
			free_dongles(dongles, i);
			return (NULL);
		}
		i++;
	}
	return (dongles);
}
