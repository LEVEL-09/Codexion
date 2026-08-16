/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 03:10:38 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/15 23:10:15 by mkhoubaz         ###   ########.fr       */
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
	*config = (t_config){
		.number_of_coders = (int)ft_atoi(argv[1]),
		.time_to_burnout = (int)ft_atoi(argv[2]),
		.time_to_compile = (int)ft_atoi(argv[3]),
		.time_to_debug = (int)ft_atoi(argv[4]),
		.time_to_refactor = (int)ft_atoi(argv[5]),
		.number_of_compiles_required = (int)ft_atoi(argv[6]),
		.number_of_coders_completed = 0,
		.flag_burnout = false,
		.status = 0
	};
	pthread_mutex_init(&config->mutex_status, NULL);
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
