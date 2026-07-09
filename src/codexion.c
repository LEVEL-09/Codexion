/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 15:10:57 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/18 16:08:06 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/* TODO:
	monitor to check coder burnout
*/

void	coder_refactoring(void *coder)
{
	t_coder			*now_coder;
	struct timespec	time;
	
	now_coder = coder;
	pthread_mutex_lock(now_coder->burn_out_mutex);
	if (*now_coder->flag_burnout == true)
	{
		pthread_mutex_unlock(now_coder->burn_out_mutex);
		return ;
	}
	pthread_mutex_unlock(now_coder->burn_out_mutex);

	printf("%ld %d is refactoring\n",
		get_time_of_now(now_coder->start_time), now_coder->id);

	clock_gettime(CLOCK_REALTIME, &time);
	time.tv_sec += now_coder->time_to_refactor / 1000;
	pthread_cond_timedwait(now_coder->cond_of_monitor, now_coder->burn_out_mutex, &time);
	return ;
}

void	coder_debugging(void *coder)
{
	t_coder			*now_coder;
	struct timespec	time;

	now_coder = coder;
	pthread_mutex_lock(now_coder->burn_out_mutex);
	if (*now_coder->flag_burnout == true)
	{
		pthread_mutex_unlock(now_coder->burn_out_mutex);
		return ;
	}
	pthread_mutex_unlock(now_coder->burn_out_mutex);

	printf("%ld %d is debugging\n",
		get_time_of_now(now_coder->start_time), now_coder->id);
	clock_gettime(CLOCK_REALTIME, &time);
	time.tv_sec += now_coder->time_to_debug / 1000;
	pthread_cond_timedwait(now_coder->cond_of_monitor, now_coder->burn_out_mutex, &time);
}

void	coder_compiling(void *coder)
{
	t_coder			*now_coder;
	long			time_of_now;
	struct timespec	time;

	// Check burn out and dongles cooldowns
	now_coder = coder;
	pthread_mutex_lock(now_coder->burn_out_mutex);
	if (*now_coder->flag_burnout == true)
	{
		pthread_mutex_unlock(now_coder->burn_out_mutex);
		return ;
	}
	pthread_mutex_unlock(now_coder->burn_out_mutex);

	if (now_coder->left_dongle->time_to_wait_dongle > get_time_of_now(now_coder->start_time))
		ft_sleep(now_coder->left_dongle->time_to_wait_dongle - get_time_of_now(now_coder->start_time));
	if (now_coder->right_dongle->time_to_wait_dongle > get_time_of_now(now_coder->start_time))
		ft_sleep(now_coder->right_dongle->time_to_wait_dongle - get_time_of_now(now_coder->start_time));

	pthread_mutex_lock(now_coder->burn_out_mutex);
	if (*now_coder->flag_burnout == true)
	{
		pthread_mutex_unlock(now_coder->burn_out_mutex);
		return ;
	}
	pthread_mutex_unlock(now_coder->burn_out_mutex);

	printf("%ld %d has taken a dongle\n",
		get_time_of_now(now_coder->start_time), now_coder->id);
	printf("%ld %d has taken a dongle\n",
		get_time_of_now(now_coder->start_time), now_coder->id);
	printf("%ld %d is compiling\n",
		get_time_of_now(now_coder->start_time), now_coder->id);
	clock_gettime(CLOCK_REALTIME, &time);
	time.tv_sec += now_coder->time_to_compile / 1000;
	pthread_cond_timedwait(now_coder->cond_of_monitor, now_coder->burn_out_mutex, &time);
	time_of_now = get_time_of_now(now_coder->start_time) + now_coder->right_dongle->cooldown;
	now_coder->left_dongle->time_to_wait_dongle = time_of_now;
	now_coder->right_dongle->time_to_wait_dongle = time_of_now;
	now_coder->number_of_compiles_required -= 1;
}

void	check_dongles_states(t_coder *coder)
{
	pthread_mutex_lock(coder->left_dongle->mutex);
	pthread_mutex_lock(coder->right_dongle->mutex);
	if (coder->left_dongle->available == true &&
		coder->right_dongle->available == true)
	{
		coder->left_dongle->available = false;
		coder->right_dongle->available = false;
		pthread_mutex_unlock(coder->left_dongle->mutex);
		pthread_mutex_unlock(coder->right_dongle->mutex);
		coder_compiling(coder);
		pthread_mutex_lock(coder->left_dongle->mutex);
		pthread_mutex_lock(coder->right_dongle->mutex);
		coder->left_dongle->available = true;
		coder->right_dongle->available = true;
		pthread_mutex_unlock(coder->left_dongle->mutex);
		pthread_mutex_unlock(coder->right_dongle->mutex);
		coder_debugging(coder);
		coder_refactoring(coder);
		return ;
	}
	pthread_mutex_unlock(coder->left_dongle->mutex);
	pthread_mutex_unlock(coder->right_dongle->mutex);
}

void	*routine(void *coder)
{
	t_coder			*now_coder;

	now_coder = coder;
	while (*now_coder->flag_burnout == false)
	{
		check_dongles_states(now_coder);
		if (now_coder->number_of_compiles_required == 0)
		{
			printf("%ld %d finish compiling required\n", get_time_of_now(now_coder->start_time), now_coder->id); /* For Debug */
			break ;
		}
	}
	return (NULL);
}

// use pthread_cond_wait
void	*monitor_check(void *monitor)
{
	int			i;
	t_coder		*coder;
	t_monitor	*now_monitor;

	i = 0;
	now_monitor = monitor;
	while (true)
	{
		coder = now_monitor->coders[i%now_monitor->number_of_coder];
		pthread_mutex_lock(now_monitor->burn_out_mutex);
		if (get_time_of_now(coder->start_time > coder->time_to_burnout))
		{
			*now_monitor->flag_burnout = true;
			pthread_cond_broadcast(&now_monitor->cond);
		}
		pthread_mutex_unlock(now_monitor->burn_out_mutex);
		i++;
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

	/* Mointor */
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
	dongles = create_dongle(number_of_coders, argv);

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
	monitor.cond = monitor_cond;
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
}
