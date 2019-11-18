/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:52:49 by chcoutur          #+#    #+#             */
/*   Updated: 2019/11/18 15:23:14 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int	print_room(size_t i, size_t j, t_stock **room)
{
	size_t	limit;
	t_stock	*cpy;
	t_stock	*cpy2;

	limit = 0;
	cpy = *room;
	cpy2 = *room;
	if (i == j)
		return (1);
	while (cpy->pipe == 1)
		cpy = cpy->next;
	while (cpy2->pipe == 1)
		cpy2 = cpy2->next;
	while (limit < i && cpy->pipe == 0)
	{
		limit++;
		cpy = cpy->next;
	}
	limit = 0;
	while (limit < j && cpy2->pipe == 0)
	{
		limit++;
		cpy2 = cpy2->next;
	}
	if (ft_strcmp(cpy->room, cpy2->room) == 0)
	{
		ft_printf("[%s] - [%s]\n i = [%lu] j = [%lu]", cpy->room, cpy2->room, i, j);
		return (-1);
	}
	return (1);
}

static int	check_tab(int *tab, t_data *env, t_stock **room)
{
	size_t	i;
	size_t	j;
	int 	tmp;

	i = 0;
	j = 0;
	tmp = 0;
	while (i < env->nb_room - 1)
	{
		while (j < env->nb_room - 1)
		{
			tmp = tab[i];
			if (tmp == tab[j + 1])
			{
				if (print_room(i, j + 1, room) == -1)
					return (-1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

static void	hash(char *str, int *tab, size_t i)
{
	int		hash;
	int		c;
	char	*strb;

	strb = str;
	hash = 0;
	c = 0;
	while ((c = *str++))
		hash = c + (hash << 1);
	tab[i] = hash;
}

int			check_name(t_data *env, t_stock **room)
{
	t_stock *cpy;
	int 	*tab;
	size_t	i;

	i = 0;
	if (!(tab = ft_memalloc(sizeof(int) * (env->nb_room))))
		return (-1);
	cpy = *room;
	while (cpy->next)
	{
		if (cpy->pipe == 0 && cpy->com == 0)
		{
			hash(cpy->room, tab, i);
			i++;
		}
		cpy = cpy->next;
	}
	if (check_tab(tab, env, room) == -1)
	{
		ft_printf(" TAB FAILED\n");
		free(tab);
		return (-1);
	}
	free(tab);
	ft_printf("TAB OK\n");
	return (1);
}
