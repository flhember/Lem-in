/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_use_bfs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:04:38 by flhember          #+#    #+#             */
/*   Updated: 2020/01/29 13:55:07 by flhember         ###   ########.fr       */
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

void		change_road_bfs(t_lst **lst, int road, t_data *env)
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
