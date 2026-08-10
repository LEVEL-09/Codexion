/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 09:27:04 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/11 00:45:24 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "coder.h"
#include "config.h"

void	swap_coder(t_coder **a, t_coder **b)
{
	t_coder		*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	min_heap(t_heap *heap, int index)
{
	int			coder;
	int			left_coder;
	int			right_coder;

	coder = index;
	left_coder = index * 2 + 1;
	right_coder = index * 2 + 2;
	if (left_coder < heap->size)
	{
		if (heap->array[left_coder]->config->time_to_burnout
			< heap->array[coder]->config->time_to_burnout)
			coder = left_coder;
	}
	if (right_coder < heap->size)
	{
		if (heap->array[right_coder]->config->time_to_burnout
			< heap->array[coder]->config->time_to_burnout)
			coder = right_coder;
	}
	if (coder != index)
	{
		swap_coder(&heap->array[coder], &heap->array[index]);
		min_heap(heap, coder);
	}
}
