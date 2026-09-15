/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 18:22:23 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/17 01:29:44 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"
#include "monitor.h"
#include "dongle.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

void	destroy_everything(t_sim *sim, int number_of_coders)
{
	if (sim->monitor)
		free(sim->monitor);
	if (sim->dongles)
		free_dongles(sim->dongles, number_of_coders);
	if (sim->coders)
		free_coders(sim->coders, number_of_coders);
	if (sim->config)
		destroy_config(sim->config);
}

static int	init_sim_core(int argc, char **argv, t_sim *sim)
{
	if (!check_argument(argc, argv))
	{
		fprintf(stderr, "Error: Invalid arguments\n");
		return (0);
	}
	sim->config = init_config(argv);
	if (!sim->config)
	{
		fprintf(stderr, "Error: Failed to initialize config\n");
		return (0);
	}
	sim->coders = create_coders(sim->config);
	if (!sim->coders)
	{
		destroy_config(sim->config);
		fprintf(stderr, "Error: Failed to create coders\n");
		return (0);
	}
	return (1);
}

int	init_simulation(int argc, char **argv, t_sim *sim)
{
	if (!init_sim_core(argc, argv, sim))
		return (0);
	sim->dongles = create_dongles(sim->config->number_of_coders, argv);
	if (!sim->dongles)
	{
		free_coders(sim->coders, sim->config->number_of_coders);
		destroy_config(sim->config);
		fprintf(stderr, "Error: Failed to create dongles\n");
		return (0);
	}
	sim->monitor = create_monitor(sim->coders, sim->config);
	if (!sim->monitor)
	{
		free_dongles(sim->dongles, sim->config->number_of_coders);
		free_coders(sim->coders, sim->config->number_of_coders);
		destroy_config(sim->config);
		fprintf(stderr, "Error: Failed to create monitor\n");
		return (0);
	}
	init_coder_with_dongles(sim->coders, sim->dongles,
		sim->config->number_of_coders);
	return (1);
}

void	join_and_cleanup(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_join(sim->coders[i]->thread, NULL) != 0)
			fprintf(stderr, "Error: Failed to join coder thread\n");
		i++;
	}
	if (pthread_join(sim->monitor->thread, NULL) != 0)
		fprintf(stderr, "Error: Failed to join monitor thread\n");
	destroy_everything(sim, sim->config->number_of_coders);
}

int	check_status(t_config *config)
{
	while (true)
	{
		pthread_mutex_lock(&config->mutex_status);
		if (config->status == 2)
		{
			pthread_mutex_unlock(&config->mutex_status);
			return (0);
		}
		else if (config->status == 1)
			break ;
		pthread_mutex_unlock(&config->mutex_status);
	}
	pthread_mutex_unlock(&config->mutex_status);
	return (1);
}
