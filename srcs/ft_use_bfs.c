/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_use_bfs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:04:38 by flhember          #+#    #+#             */
/*   Updated: 2020/01/30 15:59:10 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		reboot_nb_road(t_lst **lst)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == -1)
			(*lst)->tab[i]->road = 0;
		i++;
	}
}

void		change_part_road(t_lst **lst, int road, t_data *env)
{
	int		i;
	t_road 	*tmp;
	int		size_f;

	i = 0;
	tmp = env->road[road - 1];
	size_f = tmp->size;
	while (i <= size_f)
	{
		if (ft_strcmp((*lst)->tab[env->blk]->name, tmp->name) == 0)
			break;
		else
		{
			tmp = tmp->next;
			i++;
		}
	}
	while (tmp)
	{
		(*lst)->tab[tmp->index]->road = 0;
		tmp = tmp->next;
	}
}

void		change_all(t_lst **lst, int road)
{
	int		i;

	i = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == road)
			(*lst)->tab[i]->road = 0;
		i++;
	}
}

void		change_road_bfs(t_lst **lst, int road, t_data *env)
{
	int		flg;
	t_room	*tmp;

	flg = 0;
	tmp = (*lst)->tab[(*lst)->pos_blk_f];
	while (tmp)
	{
		if ((*lst)->tab[tmp->pos]->start == 1)
			flg = 1;
		tmp = tmp->next;
	}
	if (flg == 0)
		change_all(lst, road);
	else
		change_part_road(lst, road, env);
}

void		clean_dist(t_lst **lst)
{
	int		i;

	i = 0;
	(*lst)->size_file = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == 0)
			(*lst)->tab[i]->dist = 0;
		i++;
	}
}

void		clean_status(t_lst **lst)
{
	int		i;

	i = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == 0)
			(*lst)->tab[i]->status = 0;
		i++;
	}
}

void		del_first_file(t_file **file)
{
	t_file	*tmp;

	tmp = *file;
	*file = (*file)->next;
	free(tmp);
}
