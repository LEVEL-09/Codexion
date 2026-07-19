/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:23:45 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 05:58:09 by mkhoubaz         ###   ########.fr       */
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
# include <stdbool.h>
# include <sys/time.h>

long		ft_atoi(const char *str);
long		get_time_of_now(long start_time);
int			check_argument(int argc, char *argv[]);
void		coder_compiling(void *coder);
void		coder_debugging(void *coder);
void		coder_refactoring(void *coder);
void		dongle_cooldown(t_coder *coder, t_dongle *dongle);
void		coder_sleeping(t_coder *coder);

#endif
