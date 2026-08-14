/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 03:10:38 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/14 03:12:34 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "codexion.h"
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>

t_config	*init_config(char *argv[])
{
	t_config	*config;

	config = malloc(sizeof(t_config));
	if (!config)
		return (NULL);
	config->number_of_coders = (int)ft_atoi(argv[1]);
	config->time_to_burnout = (int)ft_atoi(argv[2]);
	config->time_to_compile = (int)ft_atoi(argv[3]);
	config->time_to_debug = (int)ft_atoi(argv[4]);
	config->time_to_refactor = (int)ft_atoi(argv[5]);
	config->number_of_compiles_required = (int)ft_atoi(argv[6]);
	config->number_of_coders_completed = 0;
	config->start_time = get_time_of_now(0);
	config->flag_burnout = false;
	pthread_mutex_init(&config->mutex_burnout, NULL);
	pthread_cond_init(&config->cond_burnout, NULL);
	return (config);
}

void	*destroy_config(t_config *config)
{
	pthread_mutex_destroy(&config->mutex_burnout);
	pthread_cond_destroy(&config->cond_burnout);
	free(config);
	return (NULL);
}
