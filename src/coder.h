/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:41:42 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 04:00:14 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "codexion.h"
# include "dongle.h"

typedef struct s_coder		t_coder;

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

t_coder		**create_coders(int number_of_coder, char *argv[], long start_time, pthread_mutex_t *mutex, bool *flag, pthread_cond_t *cond);
int			coder_check_flag(t_coder *coder);
void		check_dongles_states(t_coder *coder);

#endif
