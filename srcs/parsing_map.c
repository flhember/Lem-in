/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:26:44 by flhember          #+#    #+#             */
/*   Updated: 2019/11/07 13:19:41 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		first_line(char *line, t_data *env)
{
	//if(check_first_line(line) == -1)
	//return (-1);
	env->nb_ants = ft_atoi(line);
	if (env->nb <= 0)
		return (-1);
	return (0);
}

int		stock_room(char *line, t_room *map, t_mark *lst)
{

}

int		parsing_map(t_data *env, t_room *map, t_mark *lst)
{
	char 	*line;
	int		error;

	error = 1;
	line = NULL;
	get_next_line(0, &line);
	error = first_line(line, env)
	line ? ft_strdel(&line) : line;
	get_next_line(0, &line);
	if (error)
		init_lst(lst);
	while (error /*&& check_room(line)*/)
	{
		stock_room(line, map, lst);
		line ? ft_strdel(&line) : line;
		get_next_line(0, &line);
	}

	if (error = -1)
	{
		ft_printf("ERROR\n");
		return (-1);
	}
	return (0);
}
