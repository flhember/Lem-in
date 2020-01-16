/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:32:43 by flhember          #+#    #+#             */
/*   Updated: 2020/01/13 18:24:57 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*static void	print_file(t_file **file, t_lst **lst)
{
	t_file *cpy;

	cpy = *file;
	while (cpy)
	{
		printf("%s , %d-> ", (*lst)->tab[cpy->value]->name,
			(*lst)->tab[cpy->value]->road);
		cpy = cpy->next;
	}
	printf("\n");
}*/

static int	add_file(t_lst **lst, t_file **file, int val, int dis)
{
	t_file	*new;
	t_file	*tmp;

	new = NULL;
	tmp = *file;
	(*lst)->size_file++;
	(*lst)->tab[val]->status = 1;
	if (!(new = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	new->value = val;
	new->dist = dis;
	new->next = NULL;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int			block_bad_road(t_lst **lst, int i/*, t_file **file*/)
{
	int		flag;
	t_room *tmp;

	flag = 0;
	tmp = (*lst)->tab[i];
	(*lst)->tab[i]->road = -2;
	printf("rentre pour %s\n", (*lst)->tab[i]->name);
	while (flag == 0)
	{
		while (tmp)
		{
			if ((*lst)->tab[tmp->pos]->road == 0
				&& (*lst)->tab[tmp->pos]->dist == (*lst)->tab[i]->dist -1 && (*lst)->tab[tmp->pos]->start == 0)
			{
				ft_printf("ban le %s t'sais mort\n", (*lst)->tab[i]->name);
				(*lst)->tab[tmp->pos]->road = -2;
	//			delete_this(file, lst, i);
				i = tmp->pos;
			}
			if ((*lst)->tab[tmp->pos]->start == 1)
				return (0);
			tmp = tmp->next;
		}
		tmp = (*lst)->tab[i];
	}
	return (0);
}

int			verif_back(t_lst **lst, int pos_blk, int i)
{
	int		nb;
	int		cmp;
	int		pos;
	t_room	*tmp;
	int		flag;

	flag = 0;
	tmp = (*lst)->tab[pos_blk];
	nb = (*lst)->tab[pos_blk]->road;
	printf("check pour = %s\n", (*lst)->tab[i]->name);
	while (flag == 0)
	{
		pos = 0;
		cmp = 0;
		while (tmp)
		{
			//ft_printf("flag = %d\n", flag);
			if ((*lst)->tab[tmp->pos]->start == 1)
			{
				ft_printf("J'ai vu un start\n");
				flag = -1;
			}
			else if (tmp->pos != i && (*lst)->tab[tmp->pos]->road == 0 && (*lst)->tab[tmp->pos]->start == 0
					&& (*lst)->tab[tmp->pos]->end == 0)
			{
			//	ft_printf("cmp ++ mec!\n");
				cmp++;
			}
			else if (((*lst)->tab[tmp->pos]->road == nb || (*lst)->tab[tmp->pos]->road == -1)
					&& (*lst)->tab[tmp->pos]->dist == (*lst)->tab[pos_blk]->dist -1)
			{
			//	ft_printf("On remmonte les gars, nb = %d\n", nb);
				pos = tmp->pos;
			}
			tmp = tmp->next;
		}
		if (cmp >= 1)
			return (1);
		else if (flag == 0 && pos)
			tmp = (*lst)->tab[pos];
		ft_printf("ftft\n");
	}
	return (-1);
}

static int	check_cross(t_lst **lst, t_file **file, int i, int pos_blk)
{
	int		cmp;
	t_room	*tmp;

	cmp = 0;
	tmp = (*lst)->tab[i];
	(*lst)->cross = -1;
	while (tmp)
	{
		if ((*lst)->tab[tmp->pos]->road == -1)
			;
		else if (tmp->pos != i && (*lst)->tab[tmp->pos]->road != 0)
			(*lst)->cross = tmp->pos;
		else if (tmp->pos != i && (*lst)->tab[tmp->pos]->end == 0
				&& (*lst)->tab[tmp->pos]->dist == 0)
			cmp++;
		tmp = tmp->next;
	}
	if (cmp == 0 && (*lst)->cross != -1 && (*lst)->size_file == 1)
	{
		if (verif_back(lst, pos_blk, i) == -1)
		{
			ft_printf("\n\nCa passe!\n\n");
			block_bad_road(lst, i /*file*/);
			return (-1);
		}
		ft_printf("\n\nC'EST LA MERDE\n\n");
		change_road_bfs(lst, (*lst)->tab[(*lst)->cross]->road);
		add_file(lst, file, (*lst)->cross, (*lst)->tab[i]->dist + 1);
		(*lst)->cross = 0;
	}
	return (0);
}

static int	fill_file(t_file **file, t_lst **lst, int i)
{
	t_room	*tmp;
	int		o;

	o = 0;
	tmp = (*lst)->tab[i];
	if ((*lst)->tab[i]->end == 1)
		add_file(lst, file, i, (*lst)->tab[i]->dist + 1);
	else
	{
		while (tmp)
		{
			if (tmp->pos != i)
			{
				if ((*lst)->tab[tmp->pos]->road != 0 && (*lst)->tab[tmp->pos]->road != -2
						&& (*lst)->tab[i]->end == 0)
					check_cross(lst, file, i, tmp->pos);
				else if ((*lst)->tab[tmp->pos]->status != 0 || (*lst)->tab[tmp->pos]->road == -2)
					o = 1;
				else if ((add_file(lst, file, tmp->pos,
						(*lst)->tab[i]->dist + 1)) == -1)
					return (-1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

static int	creat_file(t_data *env, t_lst **lst, t_file **file)
{
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = (*lst)->tab[env->start];
	while (tmp)
	{
		if ((*lst)->tab[tmp->pos]->road == 0 && tmp->pos != env->start)
			i++;
		tmp = tmp->next;
	}
	if (i == 0)
		return (-1);
	if (!(*file = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	if ((fill_file(file, lst, env->start)) == -1)
	{
		free_file(file);
		return (-1);
	}
	del_first_file(file);
	(*lst)->tab[env->start]->dist = 0;
	(*lst)->tab[env->start]->status = 2;
	//print_file(file, lst);
	return (1);
}

int			bfs(t_data *env, t_lst **lst)
{
	t_file	*file;
	t_file	*tmp;

	(*lst)->ret_bfs = -1;
	tmp = NULL;
	file = NULL;
	ft_printf("ouai ouai \n");
	reboot_nb_road(lst);
	clean_dist(lst);
	if (creat_file(env, lst, &file) == -1)
		return (-1);
	tmp = file;
	while (tmp && (*lst)->ret_bfs == -1)
	{
		if ((*lst)->tab[tmp->value]->end == 1)
			(*lst)->ret_bfs = 0;
		(*lst)->tab[tmp->value]->dist = tmp->dist;
		if ((fill_file(&tmp, lst, tmp->value)) == -1)
		{
			free_file(&file);
			return (-1);
		}
		(*lst)->tab[tmp->value]->status = 2;
		tmp = tmp->next;
		(*lst)->size_file--;
	}
	clean_status(lst);
	free_file(&file);
	ft_printf("non non \n");
	return ((*lst)->ret_bfs);
}
