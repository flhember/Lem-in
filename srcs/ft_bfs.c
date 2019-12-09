/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:32:43 by flhember          #+#    #+#             */
/*   Updated: 2019/12/09 18:03:36 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static void	clean_status(t_lst **lst)
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

static void	check_cross(t_lst **lst, int i)
{
	int		cmp;
	t_room	*tmp;
	int		cross;

	cmp = 0;
	cross = 0;
	tmp = (*lst)->tab[i];
	while (tmp)
	{
		if (tmp->pos != i && (*lst)->tab[tmp->pos]->road == 1)
			cross = 1;
		else if ((*lst)->tab[tmp->pos]->status == 0 && tmp->pos != i)
		{
			printf("touch %s\n", (*lst)->tab[tmp->pos]->name);
			cmp++;
		}
		tmp = tmp->next;
	}
	printf("pour = %s, cmp = %d, cross = %d\n", (*lst)->tab[i]->name, cmp, cross);
	if (cmp == 0 && cross == 1)
		(*lst)->ret_bfs = 0;
}

static int	add_file(t_lst **lst, t_file **file, int val, int dis)
{
	t_file	*new;
	t_file	*tmp;

	new = NULL;
	tmp = *file;
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

static int	fill_file(t_file **file, t_lst **lst, int i)
{
	t_room	*tmp;
	int		o;

	o = 0;
	tmp = (*lst)->tab[i];
	while (tmp)
	{
		if (tmp->pos != i)
		{
			if ((*lst)->tab[tmp->pos]->status != 0)
				o = 1;
			else if ((*lst)->tab[tmp->pos]->road != 0)
				check_cross(lst, i);
			else if ((add_file(lst, file, tmp->pos,
					(*lst)->tab[i]->dist + 1)) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	del_first_file(t_file **file)
{
	t_file	*tmp;

	tmp = *file;
	*file = (*file)->next;
	free(tmp);
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
	return (1);
}

int			bfs(t_data *env, t_lst **lst)
{
	t_file	*file;
	t_file	*tmp;

	(*lst)->ret_bfs = -1;
	tmp = NULL;
	file = NULL;
	if (creat_file(env, lst, &file) == -1)
		return (-1);
	tmp = file;
	while (tmp)
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
	}
	clean_status(lst);
	free_file(&file);
	printf("end bfs = %d\n", (*lst)->ret_bfs);
	//print_adja(lst, env);
	return ((*lst)->ret_bfs);
}
