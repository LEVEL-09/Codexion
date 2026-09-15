/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 02:56:25 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/17 02:42:08 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"
#include "dongle.h"
#include "heap.h"
#include <stdbool.h>
#include <pthread.h>

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

void	wakeup_coders_in_heap(t_coder *coder, bool unlock_flag)
{
	if (unlock_flag)
	{
		pthread_mutex_unlock(&coder->left_dongle->mutex);
		pthread_mutex_unlock(&coder->right_dongle->mutex);
	}
	pthread_cond_signal(&coder->left_dongle->cond);
	pthread_cond_signal(&coder->right_dongle->cond);
}

void	release_dongles(t_coder *coder)
{
	extract_coder(coder->left_dongle->heap);
	extract_coder(coder->right_dongle->heap);
	wakeup_coders_in_heap(coder, true);
	coder->numbers_of_compiles += 1;
}
