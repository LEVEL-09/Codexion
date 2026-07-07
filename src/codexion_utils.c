/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 12:33:13 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/08 10:59:58 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	**create_coders(int number_of_coder, char *argv[])
{
	int			i;
	pthread_t	*thread;
	t_coder		**coders;

	coders = malloc(sizeof(t_coder *) * number_of_coder);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < number_of_coder)
	{
		coders[i] = malloc(sizeof(t_coder));
		thread = malloc(sizeof(pthread_t));
		if (!coders[i] || !thread)
			return (NULL);
		coder_init(coders[i], thread, argv, i);
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
	if (!dongles || !dongles_mutexs)
		return (NULL);
	i = 0;
	while (i < number_of_dongle)
	{
		dongles[i] = malloc(sizeof(t_dongle));
		dongles_mutexs[i] = malloc(sizeof(pthread_mutex_t));
		if (!dongles[i] || !dongles_mutexs[i])
			return (NULL);
		pthread_mutex_init(dongles_mutexs[i], NULL);
		dongle_init(dongles[i], dongles_mutexs[i], argv, i);
		i++;
	}
	return (dongles);
}

long	get_time_of_now(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		fprintf(stderr, "gettimeofday faild!\n");
		return (-1);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	coder_sleep(long dongles_cooldown_total)
{
	if (!(dongles_cooldown_total <= 0))
	{
		if (usleep(dongles_cooldown_total) != 0)
			fprintf(stderr, "usleep failed!\n");
	}
}
