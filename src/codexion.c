/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:40:18 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/06 18:52:51 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	**create_coders(int number_of_coder)
{
	int			i;
	t_coder		**coders;

	coders = malloc(sizeof(t_coder *) * number_of_coder);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < number_of_coder)
	{
		coders[i] = malloc(sizeof(t_coder));
		if (!coders[i])
			return (NULL);
		coders[i]->coder_id = i;
		i++;
	}
	return (coders);
}

t_dongle	**create_dongle(int number_of_dongle)
{
	int			i;
	t_dongle	**dongles;

	dongles = malloc(sizeof(t_dongle *) * number_of_dongle);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < number_of_dongle)
	{
		dongles[i] = malloc(sizeof(t_dongle));
		if (dongles[i])
			return (NULL);
		dongles[i]->dongle_id = i;
		i++;
	}
	return (dongles);
}

int	main(int argc, char *argv[])
{
	int			number_of_coders;
	t_coder		**coders;
	t_dongle	**dongles;

	if (!check_argument(argc, argv))
		return (fprintf(stderr, "Error: Invalid arguments\n"));
	number_of_coders = (int)ft_atoi(argv[1]);
	coders = create_coders(number_of_coders);
	dongles = create_dongle(number_of_coders);
}
