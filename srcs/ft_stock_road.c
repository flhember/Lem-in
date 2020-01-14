/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_road.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:59:05 by flhember          #+#    #+#             */
/*   Updated: 2020/01/14 17:53:03 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_adja_road(t_lst **lst, t_data *env)
{
	int		i;
	t_road	*cpy;

	i = 0;
	printf("\n\n");
	while (i < (*lst)->nb_road)
	{
		cpy = env->road[i];
		printf("\tROAD = %d, %d room: \n-name:%s", i, cpy->nb_cost, cpy->name);
		while (cpy->next)
		{
			if (cpy->next)
				printf("-> %s ", cpy->next->name);
			cpy = cpy->next;
		}
		printf("-> NULL \n\n");
		i++;
	}
	printf("\n\n");
}

int			stock_it(t_lst **lst, t_data *env, int pos, int i)
{
	t_road	*new;
	t_road	*lst_cpy;

	new = NULL;
	lst_cpy = env->road[i - 1];
	if (!(new = ft_memalloc(sizeof(t_road))))
		return (-1);
	new->name = ft_strdup((*lst)->tab[pos]->name);
	new->nb_road = i;
	new->next = NULL;
	if ((*lst)->tab[pos]->end == 1)
		env->road[i - 1]->nb_cost = ft_lstsize_road(&env->road[i - 1]) + 1;
	while (lst_cpy->next)
		lst_cpy = lst_cpy->next;
	lst_cpy->next = new;
	return (0);
}

int			find_road(t_lst **lst, t_data *env, int i, t_room *tmp)
{
	int		pos;

	pos = env->start;
	while ((*lst)->tab[pos]->end == 0)
	{
		while (tmp)
		{
			if (tmp->pos != pos && (*lst)->tab[tmp->pos]->print == 0
					&& ((*lst)->tab[tmp->pos]->road == i || (*lst)->tab[tmp->pos]->end == 1))
			{
				pos = tmp->pos;
				stock_it(lst, env, pos, i);
				if ((*lst)->tab[tmp->pos]->end == 0)
					(*lst)->tab[pos]->print = 1;
				tmp = NULL;
			}
			else
			{
				tmp = tmp->next;
				if (!tmp)
					return (-1);
			}	
		}
		tmp = (*lst)->tab[pos];
	}
	return (0);
}

int get_road_size(t_road *cpy)
{
	int i;

	i = 0;
	t_road *tmp;

	tmp = cpy;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	ft_printf("size = %d\n", i);
	return (i);
}

int get_worse(int i)
{
	return (i);
}

int get_actual(int i, t_data *env)
{
	t_road *cpy;

	cpy = env->road[i];
	cpy->size = get_road_size(cpy);
	ft_printf("size_lst env->road[%d] = %d\n", cpy->size);
	i = 0;
	while (cpy)
	{
		cpy = cpy->next;
		i++;
	}
	return (i);
}

int			get_basic_val(int i, t_data *env)
{
	int worse;
	int actual;

	worse = get_worse(i);
	actual = get_actual(i, env);
	ft_printf("ROAD [%d] -> Actual = %d | Worse = %d || TOTAL = %d\n\n", i, actual, worse, (1 + (actual - worse)));
	return (1 + (actual - worse));
}

int			ant_rep(t_data *env)
{
	int **tab;
	int i;

	i = 0;
	ft_printf("Nombre chemins = [ %d ]\n", env->nb_road_f - 1);
	if (!(tab = malloc(sizeof(int*) * (env->nb_road_f - 1))))
		return (-1);
	while (i < (env->nb_road_f - 1))
	{
		if (!(tab[i] = malloc(sizeof(int) * 1)))
			return (-1);
		tab[i][0] = get_basic_val(i, env);
		i++;
	}
	i = 0;
	while (i < ((env)->nb_road_f - 1))
	{
		ft_printf("tab[%d][0] = [ %d ]\n", i, tab[i][0]);
		i++;
	}
	return (1);
}

int			parse_road(t_lst **lst, t_data *env, t_room *tmp)
{
	int		i;
	int		er;

	i = 1;
	er = 0;
	while (i < (*lst)->nb_road)
	{
		tmp = (*lst)->tab[env->start];
		env->road[i - 1]->nb_road = i;
		env->road[i - 1]->name = ft_strdup((*lst)->tab[env->start]->name);
		if (find_road(lst, env, i, tmp) == -1)
		{
			env->road[i - 1]->name = NULL;
			printf("road %d eclate\n", i - 1);
			(*lst)->nb_road--;
		}
		i++;
	}
	return (0);
}

int			stock_road(t_lst **lst, t_data *env)
{
	int		i;

	i = 0;
	if (!(env->road = ft_memalloc(sizeof(t_road) * ((*lst)->nb_road))))
		return (-1);
	while (i < (*lst)->nb_road)
	{
		if (!(env->road[i] = ft_memalloc(sizeof(t_road))))
			return (-1);
		i++;
	}
	env->road[(*lst)->nb_road] = 0;
	parse_road(lst, env, NULL);
	print_adja_road(lst, env);
	env->nb_road_f = (*lst)->nb_road;
	ft_printf("nb env %d | nb lst %d\n", env->nb_road_f, (*lst)->nb_road);
	ant_rep(env);
	return (0);
}
