/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:23:45 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/11 00:44:50 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdbool.h>

typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_config		t_config;
typedef struct s_monitor	t_monitor;

typedef struct s_sim
{
	t_config	*config;
	t_coder		**coders;
	t_dongle	**dongles;
	t_monitor	*monitor;
}	t_sim;

void		sleep_even(t_coder *coder);
long		get_time_of_now(long start_time);
void		dongle_cooldown(t_coder *coder, t_dongle *dongle);
void		coder_sleeping(t_coder *coder, long time_to_sleep);
bool		coder_check_flag(t_coder *coder);
int			check_argument(int argc, char *argv[]);
long		ft_atoi(const char *str);
void		destroy_everything(t_sim *sim, int number_of_coders);
int			init_simulation(int argc, char **argv, t_sim *sim);
void		join_and_cleanup(t_sim *sim);

#endif
