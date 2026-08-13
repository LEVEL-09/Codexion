/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:57:25 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/13 18:01:20 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap.h"
#include "coder.h"
#include <stdlib.h>
#include <stdio.h>

t_heap	*create_heap(int capacity)
{
	t_heap		*heap;

	heap = malloc(sizeof(t_heap));
	if (!heap)
		return (NULL);
	heap->array = malloc(sizeof(t_coder *) * capacity);
	if (!heap->array)
	{
		free(heap);
		return (NULL);
	}
	heap->capacity = capacity;
	heap->size = 0;
	return (heap);
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
		fprintf(stderr, "Heap Overflow\n");
		return ;
	}
	heap->array[heap->size] = coder;
	heap->size++;
}

void	extract_coder(t_heap *heap)
{
	int			i;

	if (heap->size == 0)
	{
		fprintf(stderr, "Heap is empty\n");
		return ;
	}
	i = 0;
	while (i < heap->size - 1)
	{
		heap->array[i] = heap->array[i + 1];
		i++;
	}
	heap->array[i] = NULL;
	heap->size--;
}
