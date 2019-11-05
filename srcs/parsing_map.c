/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:26:44 by flhember          #+#    #+#             */
/*   Updated: 2019/11/05 18:23:05 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int check_line(char *line, t_room *map)
{
	(void)line;
	(void)map;
	return (1);
}

int		parsing_map(t_data *env, t_room *map)
{
	char *line;

	while ((line = ft_get_fd(0)))
	{
		if (check_line(line, map) != 1)
		{
			free(line);
			return (0);
		}
		printf("[%s]\n", line);
		free(line);
	}
	(void)map;
	printf("nb ants = %d", env->nb_ants);
	while (1)
		;
	return (0);
}

