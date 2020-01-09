/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_use_bfs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 14:04:38 by flhember          #+#    #+#             */
/*   Updated: 2020/01/07 15:47:56 by flhember         ###   ########.fr       */
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
		{
			printf("lst -1 to 0 = %s\n", (*lst)->tab[i]->name);
			(*lst)->tab[i]->road = 0;
		}
		i++;
	}
}

/*void		delete_this(t_file **file, t_lst **lst, int i)
{
	int		i;
	t_file	*tmp;

	i = 0;
	tmp = *file;
	while (file)
	{
		if (ft_strcmp((*lst)->tab[file->value]->name, (*lst)->tab[i]->name))
		{
			
			
		}	
		i++;
		tmp = tmp->next;
	}
}*/

void		change_road_bfs(t_lst **lst, int road)
{
	int		i;

	i = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == road)
		{
			printf("%s -> -1\n", (*lst)->tab[i]->name);
			(*lst)->tab[i]->road = -1;
		}
		i++;
	}
	(*lst)->tab[(*lst)->cross]->road = 0;
	printf("change = %s to 0\n", (*lst)->tab[(*lst)->cross]->name);
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
