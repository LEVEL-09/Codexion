/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 15:10:57 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 06:04:16 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* IWYU */
#include "codexion.h"
#include "coder.h"
#include "dongle.h"
#include "monitor.h"

/* TODO:
	chore fix norminette
*/

void	coder_refactoring(void *coder)
{
	t_coder			*now_coder;
	struct timespec	time;

	now_coder = coder;
	if (coder_check_flag(now_coder))
		return ;
	printf("%ld %d is refactoring\n",
		get_time_of_now(now_coder->start_time), now_coder->id);
	coder_sleeping(now_coder);
	return ;
}

void	coder_debugging(void *coder)
{
	t_coder			*now_coder;
	struct timespec	time;

	now_coder = coder;
	if (coder_check_flag(now_coder))
		return ;
	printf("%ld %d is debugging\n",
		get_time_of_now(now_coder->start_time), now_coder->id);
	coder_sleeping(now_coder);
}

void	coder_compiling(void *coder)
{
	t_coder			*now_coder;
	long			time_of_now;

	now_coder = coder;
	if (coder_check_flag(now_coder))
		return ;
	dongle_cooldown(now_coder, now_coder->left_dongle);
	if (coder_check_flag(now_coder))
		return ;
	dongle_cooldown(now_coder, now_coder->right_dongle);
	if (coder_check_flag(now_coder))
		return ;
	printf("%ld %d has taken a dongle\n",
		get_time_of_now(now_coder->start_time), now_coder->id);
	printf("%ld %d has taken a dongle\n",
		get_time_of_now(now_coder->start_time), now_coder->id);
	printf("%ld %d is compiling\n",
		get_time_of_now(now_coder->start_time), now_coder->id);
	coder_sleeping(now_coder);
	now_coder->last_time_compile = get_time_of_now(now_coder->start_time);
	time_of_now = get_time_of_now(now_coder->start_time) + now_coder->right_dongle->cooldown;
	now_coder->left_dongle->time_to_wait_dongle = time_of_now;
	now_coder->right_dongle->time_to_wait_dongle = time_of_now;
	now_coder->number_of_compiles_required -= 1;
}

void	*routine(void *coder)
{
	t_coder			*now_coder;

	now_coder = coder;
	while (true)
	{
		check_dongles_states(now_coder);
		pthread_mutex_lock(now_coder->burn_out_mutex);
		if (*now_coder->flag_burnout == true)
		{
			pthread_mutex_unlock(now_coder->burn_out_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(now_coder->burn_out_mutex);
		if (now_coder->number_of_compiles_required == 0)
		{
			printf("%ld %d finish compiling required\n", get_time_of_now(now_coder->start_time), now_coder->id); /* For Debug */
			break ;
		}
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	int				i;
	int				number_of_coders;
	t_coder			**coders;
	t_dongle		**dongles;

	bool			flag;

	flag = false;

	/* Mointor use monitor create in monitor.c*/
	t_monitor		monitor;
	pthread_t		*monitor_thread;
	pthread_cond_t	monitor_cond;
	pthread_mutex_t	mutex;

	if (!check_argument(argc, argv))
		return (fprintf(stderr, "Error: Invalid arguments\n"));
	number_of_coders = (int)ft_atoi(argv[1]);

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&monitor_cond, NULL);
	coders = create_coders(number_of_coders, argv, get_time_of_now(0), &mutex, &flag, &monitor_cond);
	dongles = create_dongles(number_of_coders, argv);

	i = 0;
	while (i < number_of_coders - 1)
	{
		coders[i]->left_dongle = dongles[i];
		coders[i]->right_dongle = dongles[i + 1];
		i++;
	}

	monitor.coders = coders;
	monitor.number_of_coder = number_of_coders;
	monitor_thread = malloc(sizeof(pthread_t));
	monitor.thread = monitor_thread;
	monitor.cond = &monitor_cond;
	monitor.burn_out_mutex = &mutex;
	monitor.flag_burnout = &flag;
	pthread_create(monitor.thread, NULL, monitor_check, &monitor);

	i = 0;
	while (i < number_of_coders - 1)
	{
		pthread_create(coders[i]->thread, NULL, routine, coders[i]);
		pthread_join(*coders[i]->thread, NULL);
		i++;
	}
	pthread_join(*monitor.thread, NULL);
}
