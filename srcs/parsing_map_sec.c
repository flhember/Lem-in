/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_sec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:46:36 by chcoutur          #+#    #+#             */
/*   Updated: 2019/12/04 15:48:23 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		add_flag(t_data *env, int flag)
{
	return (env->flags & flag);
}

int		check_nb_ants(char *str, t_data *env)
{
	int i;

	i = 0;
	if (add_flag(env, ANTS) == 0
			&& (env->se & ASTART) == 0 && (env->se & AEND) == 0)
	{
		env->flags |= ANTS;
		while (str[i])
		{
			if (ft_isdigit(str[i]) == 1)
				i++;
			else
				return (-1);
		}
		if (ft_atoi(str) > 0 && ft_atoi(str) <= 2147483647)
		{
			env->nb_ants = ft_atoi(str);
			return (1);
		}
		else
			return (-1);
	}
	return (0);
}

int		nb_split(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		check_maillon(char **tab, char *str)
{
	size_t size;

	if (nb_split(tab) == 3)
	{
		if (tab[1][0] == '-' || ft_strisdigit(tab[1]) == 1)
		{
			if (tab[1][0] == '-')
			{
				if (ft_atoi(tab[1] + 1) < -2147483647 || ft_strisdigit(tab[1] + 1) != 1)
					return (-1);
			}
			else if ((ft_strisdigit(tab[1]) != 1) || (ft_atoi(tab[1]) > 2147483647))
				return (-1);
		}
		if (tab[2][0] == '-' || ft_strisdigit(tab[2]) == 1)
		{
			//ft_printf("strisdigit(tab[2]) = %d\n", ft_strisdigit(tab[2]));
			if (tab[2][0] == '-')
			{
				if (ft_atoi(tab[2] + 1) < -2147483647 || ft_strisdigit(tab[2] + 1) != 1)
					return (-1);
			}
			else if ((ft_strisdigit(tab[2]) != 1) || (ft_atoi(tab[2]) > 2147483647))
				return (-1);
		}
		else
			return (-1);
		size = ft_strlen(tab[0]) + ft_strlen(tab[1]) + ft_strlen(tab[2]);
		if (size != (ft_strlen(str) - 2))
			return (-1);
		else
			return (1);
	}
	return (-1);
}

int		check_valid_room(char *str, t_data *env, t_stock **lst)
{
	char **tab;

	tab = NULL;
	if (!(tab = ft_strsplit(str, ' ')))
		return (-1);
//	ft_printf("%s\n", str);
	if (tab[0][0] == 'L' || tab[0][0] == '#'
			|| add_flag(env, ANTS) == 0 || (env->se & PIPE) != 0 || check_maillon(tab, str) != 1) //SI L ou # leaks?
	{
		ft_free_tab_char(tab); //Charle t'en pense quoi?
		return (-1);
	}
	creat_maillon(lst, tab[0], tab[1], tab[2]);
	if ((env->se & ASTART) != 0)
	{
		(*lst)->start = 1;
		env->se |= PSTART;
		env->se ^= ASTART;
	}
	if ((env->se & AEND) != 0)
	{
		(*lst)->end = 1;
		env->se |= PEND;
		env->se ^= AEND;
	}
	env->nb_room++;
	ft_free_tab_char(tab);
	return (1);
}
