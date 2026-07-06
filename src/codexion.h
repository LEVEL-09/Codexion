/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:23:45 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/06 06:28:41 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>

typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;
typedef struct s_heap 	t_heap;

struct s_coder
{
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;
};

struct s_dongle
{
	int				dongle_cooldown;
	pthread_mutex_t	dongle_mutex;
};

struct s_heap
{
	t_coder	**array;
	int		capacity;
	int		size;
};

int			check_argument(int argc, char *argv[]);
t_coder		coder_init(char *argv[]);
t_dongle	dongle_init(char *argv[]);
long		ft_atoi(const char *str);

#endif
