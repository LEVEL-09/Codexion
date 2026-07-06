/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/04 12:57:25 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/05 11:44:48 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

t_heap	*create_heap()
{
	t_heap *heap = malloc(sizeof(t_heap));
	heap->array = malloc(sizeof(t_coder *) * 2);
	heap->capacity = 2;
	heap->size = 0;

	return (heap);
}
