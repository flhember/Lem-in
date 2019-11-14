/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:26:44 by flhember          #+#    #+#             */
/*   Updated: 2019/11/14 11:53:20 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int check_start_end(char *str, t_data *env, t_stock **lst)
{
	if (ft_strcmp(str + 2, "start") == 0
			&& add_flag(env, START) == 0 && (env->se & AEND) == 0)
	{
		env->flags |= START;
		env->se |= ASTART;
		return (1);
	}
	else if (ft_strcmp(str + 2, "end") == 0
			&& add_flag(env, END) == 0 && (env->se & ASTART) == 0)
	{
		env->flags |= END;
		env->se |= AEND;
		return (1);
	}
	else
	{
		printf("toto\n");
		check_valid_room(str, env, lst);
		return (1);
	}
	return (-1);
}

int check_room(char *str, t_data *env, t_stock **lst)
{
	if (str[0] == '#' && str[1] == '#')
	{
		if (check_start_end(str, env, lst) == 1)
			return (1);
	}
	else if (str[0] == '#')
		return (1);
	return (-1);
}

int check_tube(char *str, t_data *env)
{
	(void)env;
	//stockage connexion
	//check si plusieurs '-'

	//if ((env->se & PSTART) == 0 || (env->se & PEND) == 0)
	//	return (0);
	if (ft_count_c(str, '-') == 1)
		return (1);
	else
		return (-1);
}

int check_line(char *str, t_data *env, t_stock **lst)
{
	if (str[0] == '#')
	{
		if (check_room(str, env, lst) == 1 && add_flag(env, ANTS) != 0)
			return (1);
	}
	else if (ft_strisdigit(str) == 1
	|| (str[0] == '-' && ft_strisdigit(str + 1) == 1))
	{
		if (check_nb_ants(str, env) == 1)
			return (1);
	}
	else if (ft_is_c(str, '-')
			&& (env->se & PSTART) != 0 && (env->se & PEND) != 0)
	{
		if (check_tube(str, env) == 1)
			return (1);
	}
	else
	{
		if (check_valid_room(str, env, lst) == 1)
			return (1);
	}
	return (-1);
}

int		parsing_map(t_data *env, t_stock **lst)
{
	char *line;

	while ((line = ft_get_fd(0)))
	{
		if (check_line(line, env, lst) != 1)
		{
			free(line);
			printf("MAP KO\n");
			return (-1);
		}
		free(line);
	}
	print_lst(lst);
	printf("\n");
	if (add_flag(env, START) && add_flag(env, END))
	{
		printf("MAP OK\n");
		return (1);
	}
	else
	{
		printf("MAP KO\n");
		return (-1);
	}
}
