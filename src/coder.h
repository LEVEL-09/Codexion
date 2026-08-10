/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:41:42 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/10 17:54:49 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include <stdbool.h>
# include <pthread.h>

typedef struct s_dongle		t_dongle;
typedef struct s_config		t_config;

typedef struct s_coder
{
	int						id;
	int						number_of_compiles_required;
	long					last_time_compile;
	bool					flag_complete;
	pthread_t				thread;
	t_dongle				*left_dongle;
	t_dongle				*right_dongle;
	t_config				*config;
}	t_coder;

void		free_coders(t_coder **coders, int count);
t_coder		**create_coders(t_config *config, int compiles_required);
void		coder_compiling(void *coder);
void		coder_debugging(void *coder);
void		coder_refactoring(void *coder);
void		init_coder_with_dongles(t_coder	**coders,
				t_dongle **dongles,
				int number_of_coders);
void		release_dongles(t_coder *coder);

#endif
