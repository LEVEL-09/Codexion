/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/07 03:10:42 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/17 01:28:35 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include <stdbool.h>
# include <pthread.h>

typedef struct s_config
{
	int						number_of_coders;
	int						time_to_burnout;
	int						time_to_compile;
	int						time_to_debug;
	int						time_to_refactor;
	int						number_of_compiles_required;
	int						number_of_coders_completed;
	long					start_time;
	bool					flag_burnout;
	short					status;
	pthread_mutex_t			mutex_status;
	pthread_mutex_t			mutex_burnout;
	pthread_cond_t			cond_burnout;
}	t_config;

t_config	*init_config(char *argv[]);
void		*destroy_config(t_config *config);
void		change_status(t_config *config, short new_status);

#endif
