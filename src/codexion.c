/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhoubaz <mkhoubaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 18:40:18 by mkhoubaz          #+#    #+#             */
/*   Updated: 2026/07/03 16:42:54 by mkhoubaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <codexion.h>

int	main(int argc, char *argv[])
{
	int			i;
	long		number_of_coders;
	t_coder		*coders_struct;
	t_dongle	*dongle_struct;

	if (!check_argument(argc, argv))
		return (fprintf(stderr, "Error: Invalid arguments\n"));

	number_of_coders = ft_atoi(argv[1]);

	coders_struct = malloc(sizeof(t_coder) * number_of_coders);
	dongle_struct = malloc(sizeof(t_dongle) * number_of_coders);

	i = 0;
	while (i < number_of_coders)
	{
		coders_struct[i] = coder_init(argv);
		dongle_struct[i] = dongle_init(argv);
		i++;
	}
}
