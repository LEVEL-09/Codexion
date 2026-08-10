/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:39:03 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/10 18:08:53 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include <pthread.h>

# define EDF 0
# define FIFO 1

typedef struct s_heap		t_heap;
typedef struct s_coder		t_coder;

typedef struct s_dongle
{
	int						id; /* For Debug */
	int						cooldown;
	long					time_to_wait_dongle;
	short					schedule;
	pthread_mutex_t			mutex;
	pthread_cond_t			cond;
	t_heap					*heap;
}	t_dongle;

t_dongle	**create_dongles(int number_of_dongle, char *argv[]);
void		free_dongles(t_dongle **dongles, int count);
void		set_dongle_wait_time(t_coder *coder, t_dongle *dongle);

#endif
