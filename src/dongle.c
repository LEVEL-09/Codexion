/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:38:38 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 04:00:32 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongle.h"
#include "coder.h"

t_dongle	**create_dongles(int number_of_dongle, char *argv[])
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
