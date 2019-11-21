/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:52:49 by chcoutur          #+#    #+#             */
/*   Updated: 2019/11/21 14:35:56 by chcoutur         ###   ########.fr       */
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
	while (cpy->pipe == 1 || cpy->com == 1)
		cpy = cpy->next;
	while (cpy2->pipe == 1 || cpy2->com == 1)
		cpy2 = cpy2->next;
	while (limit < i)
	{
		if (cpy->pipe == 0)
			limit++;
		cpy = cpy->next;
	}
	limit = 0;
	while (limit < j)
	{
		if (cpy2->pipe == 0)
			limit++;
		cpy2 = cpy2->next;
	}
	if (ft_strcmp(cpy->room, cpy2->room) == 0)
		return (-1);
	return (1);
}

static int	check_tab(int *tab, t_data *env, t_stock **room)
{
	size_t	i;
	size_t	j;
	size_t real;
	int 	tmp;
	t_stock *cpy;

	real = 0;
	cpy = *room;
	while (cpy->next)
	{
		if (cpy->com == 1)
			real++;
		cpy = cpy->next;
	}
	i = 0;
	j = 0;
	tmp = 0;
	while (i < env->nb_room)
	{
		while (j < env->nb_room)
		{
			tmp = tab[i];
			if (tmp == tab[j])
			{
				//ft_printf("tab[%lu] = [%d] tab[%lu] = [%d]\n",i,tab[i], j,tab[j]);
				if (print_room(i, j, room) == -1)
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
