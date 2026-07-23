/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:53:52 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/10 17:41:00 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include <pthread.h>

typedef struct s_coder		t_coder;
typedef struct s_config		t_config;

typedef struct s_monitor
{
	t_coder					**coders;
	pthread_t				thread;
	t_config				*config;
}	t_monitor;

void		*monitor_check(void *monitor);
t_monitor	*create_monitor(t_coder **coders, t_config *config);

#endif
