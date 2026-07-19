/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:42:42 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 06:07:50 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder.h"

static t_coder	*coder_init(t_coder *coder, char *argv[])
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

int	coder_check_flag(t_coder *coder)
{
	pthread_mutex_lock(coder->burn_out_mutex);
	if (*coder->flag_burnout == true)
	{
		pthread_mutex_unlock(coder->burn_out_mutex);
		return (1);
	}
	pthread_mutex_unlock(coder->burn_out_mutex);
	return (0);
}

void	check_dongles_states(t_coder *coder)
{
	pthread_mutex_lock(coder->left_dongle->mutex);
	pthread_mutex_lock(coder->right_dongle->mutex);
	if (coder->left_dongle->available == true
		&& coder->right_dongle->available == true)
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
