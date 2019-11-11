/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:26:44 by flhember          #+#    #+#             */
/*   Updated: 2019/11/11 11:52:25 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int add_flag(t_data *env, int flag)
{
	return (env->flags & flag);
}

int check_nb_ants(char *str, t_data *env)
{
	int i;

	i = 0;
	if (add_flag(env, ANTS) == 0 && (env->se & ASTART) == 0 && (env->se & AEND) == 0)
	{
		env->flags |= ANTS;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else
			return (0);
	}
	return (1);
	}
	return (0);
}

int check_valid_room(char *str, t_data *env, t_stock *lst)
{
	char **split;

	(void)env;
	split = NULL;
	if (ft_count_c(str, ' ') != 2)
		return (0);
	else
	{
		split = ft_strsplit(str, ' ');
		if (split[0][0] == 'L' || split[0][0] == '#')
		{
			ft_free_tab_char(split);
			return (0);
		}
		creat_maillon(lst, split[0], split[1], split[2], 0); //
		ft_free_tab_char(split);
		free(split);
	}
	if ((env->se & ASTART) != 0)
	{
		env->se |= PSTART;
		env->se ^= ASTART;
	}
	if ((env->se & AEND) != 0)
	{
		env->se |= PEND;
		env->se ^= AEND;
	}
	return (1);
}

int check_start_end(char *str, t_data *env, t_stock *lst)
{
	if (ft_strcmp(str + 2, "start") == 0 && add_flag(env, START) == 0 && (env->se & AEND) == 0)
	{
		env->flags |= START;
		env->se |= ASTART;
		return (1);
	}
	else if (ft_strcmp(str + 2, "end") == 0 && add_flag(env, END) == 0 && (env->se & ASTART) == 0)
	{
		env->flags |= END;
		env->se |= AEND;
		return (1);
	}
	else
	{
		check_valid_room(str, env, lst);
		return (1);
	}
	return (0);
}

int check_room(char *str, t_data *env, t_stock *lst)
{
	if (str[0] == '#' && str[1] == '#')
	{
		if (check_start_end(str, env, lst) == 1)
			return (1);
	}
	else if (str[0] == '#')
		return (1);
	return (0);
}

int check_tube(char *str, t_data *env)
{
	if ((env->se & PSTART) == 0 || (env->se & PEND) == 0)
		return (0);
	if (ft_count_c(str, '-') == 1)
		return (1);
	else
		return (0);
}

int check_line(char *str, t_data *env, t_stock *lst)
{
	if (str[0] == '#')
	{
		if (check_room(str, env, lst) == 1 && add_flag(env, ANTS) != 0)
			return (1);
	}
	else if (ft_strisdigit(str) == 1
	|| (str[0] == '-' && ft_strisdigit(str + 1) ==1))
	{
		if (check_nb_ants(str, env) == 1)
			return (1);
	}
	else if (ft_is_c(str, '-'))
	{
		if (check_tube(str, env) == 1)
			return (1);
	}
	else
	{
		if (check_valid_room(str, env, lst) == 1)
			return (1);
	}
	return (0);
}

int		parsing_map(t_data *env, t_stock *lst)
{
	char *line;

	while ((line = ft_get_fd(0)))
	{
		if (check_line(line, env, lst) == 0)
		{
			free(line);
			printf("MAP KO\n");
			return (0);
		}
		free(line);
	}
	add_flag(env, START) && add_flag(env, END) ? printf("MAP OK\n") : printf("MAP KO\n");
	//print_lst(lst);
	return (0);
}

