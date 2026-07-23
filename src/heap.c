/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:57:25 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/25 06:46:22 by mkhoubaz         ###   ########.fr       */
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

t_coder	*extract_coder(t_heap *heap)
{
	t_coder		*root_coder;
	int			i;

	if (heap->size == 0)
	{
		fprintf(stderr, "Heap is empty\n");
		return (NULL);
	}
	else if (heap->size == 1)
	{
		heap->size--;
		return (heap->array[0]);
	}
	root_coder = heap->array[0];
	i = 0;
	while (i < heap->size)
	{
		heap->array[i] = heap->array[i + 1];
		i++;
	}
	heap->size--;
	return (root_coder);
}
