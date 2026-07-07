/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 15:10:57 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/08 11:10:44 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	coder_debugging(t_coder *coder, long start_time)
{
	printf("%ld %d is debugging\n", get_time_of_now() - start_time, coder->id);
	if (usleep(coder->time_to_debug) != 0)
	{
		fprintf(stderr, "usleep failed!\n");
		return (-1);
	}
	return (1);
}

int	coder_refactoring(t_coder *coder, long start_time)
{
	printf("%ld %d is refactoring\n", get_time_of_now() - start_time, coder->id);
	if (usleep(coder->time_to_refactor) != 0)
	{
		fprintf(stderr, "usleep failed!\n");
		return (-1);
	}
	return (1);
}

void	*coder_compiling(void *coder)
{
	long			dongles_cooldown_total;
	t_coder			*now_coder;

	now_coder = coder;
	pthread_mutex_lock(now_coder->left_dongle->mutex);
	pthread_mutex_lock(now_coder->right_dongle->mutex);
	dongles_cooldown_total = now_coder->left_dongle->cooldown - get_time_of_now();
	coder_sleep(dongles_cooldown_total);
	dongles_cooldown_total = now_coder->right_dongle->cooldown - get_time_of_now();
	coder_sleep(dongles_cooldown_total);
	printf("%ld %d is compiling\n", get_time_of_now() - now_coder->start_time, now_coder->id);
	if (usleep(now_coder->time_to_compile) != 0)
	{
		fprintf(stderr, "usleep failed!\n");
		return (NULL);
	}

	pthread_mutex_unlock(now_coder->left_dongle->mutex);
	pthread_mutex_unlock(now_coder->right_dongle->mutex);
	coder_debugging(coder, now_coder->start_time);
	coder_refactoring(coder, now_coder->start_time);
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int			i;
	int			number_of_coders;
	t_coder		**coders;
	t_dongle	**dongles;

	if (!check_argument(argc, argv))
		return (fprintf(stderr, "Error: Invalid arguments\n"));
	number_of_coders = (int)ft_atoi(argv[1]);
	coders = create_coders(number_of_coders, argv);
	dongles = create_dongle(number_of_coders, argv);

	i = 0;
	while (i < number_of_coders)
	{
		coders[i]->left_dongle = dongles[i];
		coders[i]->right_dongle = dongles[i + 1];
		pthread_create(coders[i]->thread, NULL, coder_compiling, NULL);
		pthread_join(*coders[i]->thread, NULL);
		i++;
	}
}
