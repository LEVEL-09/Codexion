/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:34:55 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/08/10 17:41:21 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

typedef struct s_coder		t_coder;

typedef struct s_heap
{
	t_coder					**array;
	int						capacity;
	int						size;
}	t_heap;

t_heap		*create_heap(int capacity);
void		heapify(t_heap *heap);
void		insert_heap(t_heap	*heap, t_coder *coder);
t_coder		*extract_coder(t_heap *heap);
void		min_heap(t_heap *heap, int index);
void		swap_coder(t_coder **a, t_coder **b);

#endif
