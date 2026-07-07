/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:57:25 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/07 06:29:32 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_heap	*create_heap(int capacity)
{
	t_heap		*heap;

	heap = malloc(sizeof(t_heap));
	heap->array = malloc(sizeof(t_coder *) * capacity);
	heap->capacity = capacity;
	heap->size = 0;
	return (heap);
}

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
		if (heap->array[left_coder]->time_to_burnout
			< heap->array[coder]->time_to_burnout)
			coder = left_coder;
	}
	if (right_coder < heap->size)
	{
		if (heap->array[right_coder]->time_to_burnout
			< heap->array[coder]->time_to_burnout)
			coder = right_coder;
	}
	if (coder != index)
	{
		swap_coder(&heap->array[coder], &heap->array[index]);
		min_heap(heap, coder);
	}
}

void	heapify(t_heap *heap)
{
	int			start_index;

	start_index = (heap->size / 2) - 1;
	while (start_index >= 0)
	{
		min_heap(heap, start_index);
		start_index--;
	}
}

void	insert_heap(t_heap	*heap, t_coder *coder)
{
	if (heap->size >= heap->capacity)
	{
		printf("Heap Overflow\n");
		return ;
	}
	heap->array[heap->size] = coder;
	heap->size++;
}
