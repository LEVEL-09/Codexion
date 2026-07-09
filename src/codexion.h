/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:23:45 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/18 16:07:07 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>

typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_heap		t_heap;
typedef struct s_monitor	t_monitor;

struct s_coder
{
	int						id;
	int						time_to_burnout;
	int						time_to_compile;
	int						time_to_debug;
	int						time_to_refactor;
	int						number_of_compiles_required;
	bool					*flag_burnout;
	long					start_time;
	long					last_time_compile;
	pthread_t				*thread;
	t_dongle				*left_dongle;
	t_dongle				*right_dongle;
	pthread_mutex_t			*burn_out_mutex;
	pthread_cond_t			*cond_of_monitor;
};

struct s_dongle
{
	int						id; /* For Debug */
	int						cooldown; /* move it to s_coder struct */
	long					time_to_wait_dongle;
	bool					available;
	pthread_mutex_t			*mutex;
};

struct s_heap
{
	t_coder					**array;
	int						capacity;
	int						size;
};

struct s_monitor
{
	int						number_of_coder;
	pthread_t				*thread;
	pthread_cond_t			cond;
	pthread_mutex_t			*burn_out_mutex;
	t_coder					**coders;
	bool					*flag_burnout;
};

void		ft_sleep(int time);
long		ft_atoi(const char *str);
long		get_time_of_now(long start_time);
void		min_heap(t_heap *heap, int index);
void		swap_coder(t_coder **a, t_coder **b);
int			check_argument(int argc, char *argv[]);
t_dongle	**create_dongle(int number_of_dongle, char *argv[]);
t_coder		**create_coders(int number_of_coder, char *argv[], long start_time, pthread_mutex_t *mutex, bool *flag, pthread_cond_t *cond);

#endif
