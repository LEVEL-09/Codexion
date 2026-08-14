/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 02:56:25 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/14 05:11:42 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "dongle.h"
#include "config.h"
#include "codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <heap.h>

void	init_coder_with_dongles(t_coder	**coders,
									t_dongle **dongles,
									int number_of_coders)
{
	int	i;

	if (number_of_coders == 1)
	{
		coders[0]->right_dongle = NULL;
		coders[0]->left_dongle = dongles[0];
		return ;
	}
	coders[0]->right_dongle = dongles[number_of_coders - 1];
	coders[0]->left_dongle = dongles[0];
	i = 1;
	while (i < number_of_coders)
	{
		coders[i]->right_dongle = dongles[i - 1];
		coders[i]->left_dongle = dongles[i];
		i++;
	}
}

void	release_dongles(t_coder *coder)
{
	printf("%ld %d is compiling\n",
		get_time_of_now(coder->config->start_time), coder->id);
	coder_sleeping(coder, coder->config->time_to_compile);
	extract_coder(coder->left_dongle->heap);
	extract_coder(coder->right_dongle->heap);
	pthread_mutex_unlock(&coder->left_dongle->mutex);
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	pthread_cond_signal(&coder->left_dongle->cond);
	pthread_cond_signal(&coder->right_dongle->cond);
	coder->numbers_of_compiles += 1;
}
