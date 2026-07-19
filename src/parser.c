/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:28:06 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/22 05:02:05 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	check_number(char *s)
{
	int			i;

	i = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (!('0' <= s[i] && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int	check_scheduler(char *s)
{
	if (!strcmp(s, "fifo") || !strcmp(s, "edf"))
		return (1);
	return (0);
}

int	check_argument(int argc, char *argv[])
{
	int			i;
	long		number;

	if (argc != 9)
		return (0);
	else if (!check_number(argv[1])
		|| !check_number(argv[2])
		|| !check_number(argv[3])
		|| !check_number(argv[4])
		|| !check_number(argv[5])
		|| !check_number(argv[6])
		|| !check_number(argv[7])
		|| !check_scheduler(argv[8]))
		return (0);
	i = 1;
	while (i != 8)
	{
		number = ft_atoi(argv[i]);
		if (number > INT_MAX || number == -1)
			return (0);
		i++;
	}
	return (1);
}
