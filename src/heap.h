/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 02:34:55 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 05:30:15 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_H
# define HEAP_H

# include "codexion.h"
# include "coder.h"

typedef struct s_heap		t_heap;

struct s_heap
{
	t_coder					**array;
	int						capacity;
	int						size;
};

void		min_heap(t_heap *heap, int index);
void		swap_coder(t_coder **a, t_coder **b);

#endif
