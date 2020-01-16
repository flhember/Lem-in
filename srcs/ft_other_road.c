/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_road.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 17:00:08 by flhember          #+#    #+#             */
/*   Updated: 2020/01/14 17:53:00 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		check_nb_road(t_lst **lst)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == -1)
			check = 1;
		i++;
	}
	if (check == 1)
		(*lst)->nb_road--;
}
/*
void		change_road(t_lst **lst, int road, int new_road)
{
	int		i;

	i = 0;
	printf("je passe\n");
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == new_road)
			(*lst)->tab[i]->road = 0;
		if ((*lst)->tab[i]->road == road)
			(*lst)->tab[i]->road = new_road;
		i++;
	}
	(*lst)->tab[(*lst)->cross]->road = new_road;
	(*lst)->nb_road = new_road;
}

int			verif_cross(t_lst **lst, int i)
{
	int		cmp;
	t_room	*tmp;
	int		cross;

	cmp = 0;
	cross = 0;
	tmp = (*lst)->tab[i];
	if (i < 0 || i == (*lst)->nb_room)
		return (-1);
	while (tmp)
	{
		if (tmp->pos != i)
		{
			if ((*lst)->tab[tmp->pos]->road != (*lst)->tab[i]->road)
			{
				cross = 1;
				(*lst)->cross = tmp->pos;
			}
			else if ((*lst)->tab[tmp->pos]->road != (*lst)->nb_road)
				cmp++;
		}
		tmp = tmp->next;
	}
	printf("pour %s , cmp = %d, cross = %d\n", (*lst)->tab[i]->name, cmp, cross);
	if (cmp == 0 && cross == 1)
		return (1);
	return (-1);
}*/

static int	pars_pipe_best(t_lst **lst, t_room *tmp, int i, int j)
{
	tmp = (*lst)->tab[j];
	while (tmp)
	{
		if (tmp->pos == (*lst)->tab[i]->pos && (*lst)->tab[j]->road == 0)
		{
			if ((*lst)->tab[j]->start == 0 && (*lst)->tab[j]->end == 0)
				(*lst)->tab[j]->road = (*lst)->nb_road;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	other_road_bis(t_lst **lst, int ds, int i, int j)
{
	//ft_printf("EEEEAAAAASYYYYY Lem-in\n");
	while ((*lst)->tab[j]->start == 0)
	{
		if (j > (*lst)->nb_room || ds < 0)
			return (-1);
		if ((*lst)->tab[j]->dist == ds && (*lst)->tab[j]->road == 0)
		{
	//		ft_printf("je rentre\n");
			if ((pars_pipe_best(lst, NULL, i, j)) == 0)
				j++;
			else
			{
				i = j;
				j = 0;
				ds--;
			}
		}
		else
		{
	//		ft_printf("i = %d\n", i);
			//ft_printf("j = %d | nb_room = %d\n", j, (*lst)->nb_room);
			j++;
		}
	}
	return (0);
}

/*
static int	other_road_bis(t_lst **lst, int ds, int i, int j)
{
	if (ds > (*lst)->tab[(*lst)->end]->dist || ds < 0)
		return (-1);
	if (j > (*lst)->nb_room)
	{
		if (other_road_bis(lst, ds++, i, 0) == -1)
			return (-1);
	}
	else if ((*lst)->tab[j]->dist != ds || (*lst)->tab[j]->road != 0 || (*lst)->tab[j]->end == 1)
		other_road_bis(lst, ds, i, ++j);
	else if ((*lst)->tab[j]->dist == ds && (*lst)->tab[j]->road == 0)
	{
		if ((pars_pipe_best(lst, NULL, i, j)) == 1)
		{
			if ((*lst)->tab[j]->start == 1)
				return (1);
			else
				other_road_bis(lst, --ds, j, 0);
		}
		else
			other_road_bis(lst, ds, i, ++j);
	}
	return (0);
}
*/


int			other_road(t_lst **lst, t_data *env)
{
	int		i;
	int		ds;

	ds = 0;
	i = env->end;
	(*lst)->end = i;
	printf("nb room = %d\n", (*lst)->nb_room);
	(*lst)->nb_road++;
	int	t = 0;
	while (bfs(env, lst) == 0)
//	while (t < 40)
	{
//		bfs(env, lst);
//		print_adja(lst, env);
		ft_printf("nb_road = %d\n", (*lst)->nb_road);
		check_nb_road(lst);
		ds = (*lst)->tab[(*lst)->end]->dist;
		if ((other_road_bis(lst, --ds, (*lst)->end, 0)) == -1)
			return (-1);
		ft_printf("nb_road = %d\n", (*lst)->nb_road);
		(*lst)->nb_road++;
		t++;
	}
//	print_adja(lst, env);
	printf("nb road possible = %d\nnb road find= %d\n", env->nb_pos, (*lst)->nb_road);
	//print_road(lst, env, NULL);
	return (0);
}
