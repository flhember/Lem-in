/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_road.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:59:05 by flhember          #+#    #+#             */
/*   Updated: 2020/01/23 18:37:21 by chcoutur         ###   ########.fr       */
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
		(*lst)->total_room += cpy->nb_cost;
		while (cpy->next)
		{
			if (cpy->next)
				printf("-> %s ", cpy->next->name);
			cpy = cpy->next;
		}
		printf("-> NULL \n\n");
		i++;
	}
	ft_printf("[cost = %d] [total = %d]\n", cpy->nb_cost, (*lst)->total_room);
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
	new->index = (*lst)->tab[pos]->pos;
	new->next = NULL;
	if ((*lst)->tab[pos]->end == 1)
		env->road[i - 1]->nb_cost = ft_lstsize_road(&env->road[i - 1]) + 1;
	while (lst_cpy->next)
		lst_cpy = lst_cpy->next;
	lst_cpy->next = new;
	return (0);
}

void		reboot_print(t_lst **lst)
{
	int		i;

	i = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->print == 1)
			(*lst)->tab[i]->print = 0;
		i++;
	}
}
int			find_road(t_lst **lst, t_data *env, int i, t_room *tmp)
{
	env->tmp_pos = env->start;
	while ((*lst)->tab[env->tmp_pos]->end == 0)
	{
		while (tmp)
		{
			if (tmp->pos != env->tmp_pos && (((*lst)->tab[tmp->pos]->road == i
						&& (*lst)->tab[tmp->pos]->print == 0) || (*lst)->tab[tmp->pos]->end == 1))
			{
				//if ((*lst)->tab[tmp->pos]->end == 0)
				(*lst)->tab[tmp->pos]->print = 1;
				env->tmp_pos = tmp->pos;
				stock_it(lst, env, env->tmp_pos, i);
				tmp = NULL;
			}
			else
			{
				tmp = tmp->next;
				if (!tmp)
					return (-1);
			}
		}
		tmp = (*lst)->tab[env->tmp_pos];
	}
	return (0);
}

int			parse_road(t_lst **lst, t_data *env, t_room *tmp)
{
	int		i;

	i = 1;
	while (i <= (*lst)->nb_road)
	{
		total += env->road[i]->nb_cost * env->road[i]->ants;
		i++;
	}
	i =0;
	while (i < total)
	{
		while (j < limit)
		{
			env->road[i - 1]->nb_road = 0;
			ft_strdel(&(env->road[i - 1]->name));
		}
		j = 0;
		i++;
	}
	ft_printf("Total = %d\n", total);
}

int		ants_treat(t_lst **lst, t_data *env)
{
	(*lst)->nb_road--;
	int limit;
	int i;
	int total_cost;
	int cmp;

	i = 0;
	cmp = 0;
	limit = 1;
	total_cost = treat_better(limit, env);
//	ft_printf("Pour %d fourmis\n", env->nb_ants);
//	ft_printf("total_cost = %5d | limit = %5d | nb_road = %5d\n\n", total_cost, limit, (*lst)->nb_road);
	while (limit < (*lst)->nb_road)
	{
		limit++;
		cmp = total_cost;
		total_cost = treat_better(limit, env);
		ft_printf("[ total_cost = %5d | limit = %5d | nb_road = %5d ]\n", total_cost, limit, (*lst)->nb_road);
	//	ft_printf("total_cost = %d | tmp = %d\n", total_cost, cmp);
	//		ft_printf("i++ %d\n\n", i);
		if (total_cost >= cmp)
		{
			i++;
			//if (total_cost > cmp)
				total_cost = cmp;
		}
	}
	if (limit > (*lst)->nb_road)
	{
//		ft_printf("ca va pas etre possible mon pote, on fait pas de la magie ici\n");
		return (-1);
	}
//	ft_printf("\nCHECK total_cost = %5d | limit = %5d | nb_road = %5d | i = %5d\n", total_cost, limit, (*lst)->nb_road, i);
	limit -= i;
	ft_printf("\ntotal_cost = %5d | limit = %5d | nb_road = %5d\n", total_cost, limit, (*lst)->nb_road);
//	ft_printf("\n\n____________________________________________\n\n");
//	ft_printf("Taille tableau = [ %d ]\n", limit);
	i = 0;
	ft_printf("Nombres de coups en passant par %d chemins = %d\n", limit, total_cost);
	final_rep(limit, total_cost, env);
	display(limit, total_cost, env);
	return (1);
}

int			stock_start_end(t_lst **lst, t_data *env)
{
	if (!(env->road = ft_memalloc(sizeof(t_road) * 1)))
		return (-1);
	if (!(env->road[0] = ft_memalloc(sizeof(t_road))))
		return (-1);
	env->road[0]->nb_road = 0;
	env->road[0]->name = ft_strdup((*lst)->tab[env->start]->name);
	stock_it(lst, env, env->end, 1);
	env->nb_road_f = 1;
	print_adja_road(lst, env);
	return (0);
}

int			stock_road_other(t_lst **lst, t_data *env)
{
	t_room	*tmp;

	tmp = (*lst)->tab[env->start];
	ft_printf("la?, nb ro %d\n", (*lst)->nb_road);
	printf("t = %d\n", (env->nb_pos * 2));
	env->road[(*lst)->nb_road - 1]->nb_road = (*lst)->nb_road;
	env->road[(*lst)->nb_road - 1]->name = ft_strdup((*lst)->tab[env->start]->name);
	find_road(lst, env, (*lst)->nb_road, tmp);
	env->road[(*lst)->nb_road - 1]->size = ft_lstsize_road(&env->road[(*lst)->nb_road - 1]);
	reboot_print(lst);
	return (0);
}

int			stock_road(t_lst **lst, t_data *env)
{
	parse_road(lst, env, NULL);
	print_adja_road(lst, env);
	env->nb_road_f = (*lst)->nb_road;
	return (0);
}

int			creat_road(t_lst **lst, t_data *env)
{
	int		i;
	(void)lst;

	i = 0;
	if (!(env->road = ft_memalloc(sizeof(t_road) * (env->nb_pos * 2))))
		return (-1);
	while (i < (env->nb_pos * 2))
	{
		if (!(env->road[i] = ft_memalloc(sizeof(t_road))))
			return (-1);
		i++;
	}
	env->road[env->nb_pos * 2] = 0;
	return (0);
}
