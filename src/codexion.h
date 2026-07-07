/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:23:45 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/08 11:44:08 by mkhoubaz         ###   ########.fr       */
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

typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_heap		t_heap;

struct s_coder
{
	int						id;
	int						time_to_burnout;
	int						time_to_compile;
	int						time_to_debug;
	int						time_to_refactor;
	int						number_of_compiles_required;
	long					start_time;
	pthread_t				*thread;
	t_dongle				*left_dongle;
	t_dongle				*right_dongle;

};

struct s_dongle
{
	int						id; /* For Debug */
	int						cooldown;
	pthread_mutex_t			*mutex;
};

struct s_heap
{
	t_coder					**array;
	int						capacity;
	int						size;
};

int							check_argument(int argc, char *argv[]);
void						swap_coder(t_coder **a, t_coder **b);
t_coder						*coder_init(t_coder *coder, pthread_t *thread, char *argv[], int i);
t_dongle					*dongle_init(t_dongle *dongle, pthread_mutex_t *mutex, char *argv[], int i);
long						ft_atoi(const char *str);
void						coder_sleep(long dongles_cooldown_total);
t_coder						**create_coders(int number_of_coder, char *argv[]);
t_dongle					**create_dongle(int number_of_dongle, char *argv[]);
long						get_time_of_now(void);

#endif
