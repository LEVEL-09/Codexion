/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 10:29:45 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/06 15:32:00 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_sp(char s)
{
	if (s == '\n' || s == '\t' || s == '\v'
		|| s == '\f' || s == '\r' || s == ' ')
		return (1);
	return (0);
}

static int	ft_overflow(int neg)
{
	if (neg < 0)
		return (0);
	return (-1);
}

long		ft_atoi(const char *str)
{
	int			i;
	int			neg;
	long		cont;
	long		overflow;

	i = 0;
	neg = 1;
	while (check_sp(str[i]))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i++] == 45)
			neg = -1;
	}
	cont = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		overflow = cont;
		cont *= 10;
		cont = cont + (str[i] - '0');
		if (overflow != cont / 10)
			return (ft_overflow(neg));
		i++;
	}
	return (cont * neg);
}
