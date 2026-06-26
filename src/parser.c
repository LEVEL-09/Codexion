/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:28:06 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/03 16:18:38 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	check_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!('0' <= s[i] && s[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_scheduler(char *s)
{
	if (!strcmp(s, "fifo") || !strcmp(s, "edf"))
		return (1);
	return (0);
}

int	check_argument(int argc, char *argv[])
{
	int		i;
	long	number;

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
			return (fprintf(stderr, "max number is MAX_INT\n"));
		i++;
	}
	return (1);
}

t_coder coder_init(char *argv[])
{
	t_coder	coder;

	coder.time_to_burnout = ft_atoi(argv[2]);
	coder.time_to_compile = ft_atoi(argv[3]);
	coder.time_to_debug = ft_atoi(argv[4]);
	coder.time_to_refactor = ft_atoi(argv[5]);
	coder.number_of_compiles_required = ft_atoi(argv[6]);
	return (coder);
}

t_dongle dongle_init(char *argv[])
{
	t_dongle	dongle;

	dongle.dongle_cooldown = ft_atoi(argv[7]);
	return (dongle);
}
