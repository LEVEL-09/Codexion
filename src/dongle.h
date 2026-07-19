/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:39:03 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 04:00:09 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include "codexion.h"

typedef struct s_dongle		t_dongle;

struct s_dongle
{
	int						id; /* For Debug */
	int						cooldown; /* move it to s_coder struct */
	long					time_to_wait_dongle;
	bool					available;
	pthread_mutex_t			*mutex;
};

t_dongle	**create_dongles(int number_of_dongle, char *argv[]);

#endif
