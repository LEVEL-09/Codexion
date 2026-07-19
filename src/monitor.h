/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:53:52 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 02:56:16 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include "codexion.h"
# include "coder.h"

typedef struct s_monitor	t_monitor;

struct s_monitor
{
	int						number_of_coder;
	pthread_t				*thread;
	pthread_cond_t			*cond;
	pthread_mutex_t			*burn_out_mutex;
	t_coder					**coders;
	bool					*flag_burnout;
};

void	*monitor_check(void *monitor);

#endif
