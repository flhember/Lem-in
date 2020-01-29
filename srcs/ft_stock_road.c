/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stock_road.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 14:59:05 by flhember          #+#    #+#             */
/*   Updated: 2020/01/29 14:06:27 by flhember         ###   ########.fr       */
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
		tmp = (*lst)->tab[env->start];
		env->road[i - 1]->nb_road = i;
		env->road[i - 1]->name = ft_strdup((*lst)->tab[env->start]->name);
		if (find_road(lst, env, i, tmp) == -1)
		{
			env->road[i - 1]->nb_road = 0;
			ft_strdel(&(env->road[i - 1]->name));
		}
		i++;
	}
	return (0);
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
