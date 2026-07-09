/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:33:13 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/18 16:06:55 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*coder_init(t_coder *coder, char *argv[])
{
	coder->time_to_burnout = ft_atoi(argv[2]);
	coder->time_to_compile = ft_atoi(argv[3]);
	coder->time_to_debug = ft_atoi(argv[4]);
	coder->time_to_refactor = ft_atoi(argv[5]);
	coder->number_of_compiles_required = ft_atoi(argv[6]);
	return (coder);
}

t_coder	**create_coders(int number_of_coder, char *argv[], long start_time, pthread_mutex_t *mutex, bool *flag, pthread_cond_t *cond)
{
	int			i;
	pthread_t	*thread;
	t_coder		**coders;

	coders = malloc(sizeof(t_coder *) * number_of_coder);
	i = 0;
	while (i < number_of_coder)
	{
		coders[i] = malloc(sizeof(t_coder));
		thread = malloc(sizeof(pthread_t));
		coders[i]->id = i + 1;
		coder_init(coders[i], argv);
		coders[i]->flag_burnout = flag;
		coders[i]->start_time = start_time;
		coders[i]->last_time_compile = 0;
		coders[i]->thread = thread;
		coders[i]->burn_out_mutex = mutex;
		coders[i]->cond_of_monitor = cond;
		i++;
	}
	return (coders);
}

t_dongle	**create_dongle(int number_of_dongle, char *argv[])
{
	int				i;
	t_dongle		**dongles;
	pthread_mutex_t	**dongles_mutexs;

	dongles = malloc(sizeof(t_dongle *) * number_of_dongle);
	dongles_mutexs = malloc(sizeof(pthread_mutex_t *) * number_of_dongle);
	i = 0;
	while (i < number_of_dongle)
	{
		dongles[i] = malloc(sizeof(t_dongle));
		dongles_mutexs[i] = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(dongles_mutexs[i], NULL);
		dongles[i]->id = i + 1;
		dongles[i]->cooldown = ft_atoi(argv[7]);
		dongles[i]->time_to_wait_dongle = 0;
		dongles[i]->available = true;
		dongles[i]->mutex = dongles_mutexs[i];
		i++;
	}
	return (dongles);
}

long	get_time_of_now(long start_time)
{
	struct timeval	time;
	long			result;

	gettimeofday(&time, NULL);
	result = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (result - start_time);
}

void	ft_sleep(int time)
{
	usleep(time * 1000);
}
