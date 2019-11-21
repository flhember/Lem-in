/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:42:48 by flhember          #+#    #+#             */
/*   Updated: 2019/11/21 15:43:33 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_file(t_file **file, t_lst **lst)
{
	t_file *tmp;

	tmp = *file;
	while (tmp->next)
	{
		printf("[%d -> %s] -> ", tmp->value, (*lst)->tab[tmp->value]->name);
		tmp = tmp->next;
	}
	printf("NULL\n");
}

int			add_file(t_file **file, int val)
{
	t_file	*new;
	t_file	*tmp;

	new = NULL;
	tmp = *file;
	printf("val = %d\n", val);
	if (!(new = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	new->value = val;
	new->next = NULL;
	if ((*file)->next == NULL)
	{
		printf("oui\n");
		*file = new;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

int			fill_file(t_file **file, t_lst **lst, int i)
{
	t_room *tmp;

	tmp = (*lst)->tab[i];
	if ((*lst)->tab[i]->status == 1)
		return (1);
	while (tmp)
	{
		printf("status = %d de %s\n", (*lst)->tab[i]->status, (*lst)->tab[i]->name);
		if ((*lst)->tab[i]->status == 0 && tmp->pos != i)
		{
			printf("%d %s\n", tmp->pos, tmp->name);
			if ((add_file(file, tmp->pos)) == -1)
				return (-1);
			(*lst)->tab[tmp->pos]->status = 1;
		}
		tmp = tmp->next;
	}
	return (0);
}

void		del_first_file(t_file **file)
{
	t_file	*tmp;

	tmp = (*file)->next;
	free(file);
	*file = tmp;
}

void		bfs(t_file **file, t_lst **lst)
{
	int		i;

	i = 1;
	while ((*file)->next)
	{
		(*lst)->tab[(*file)->value]->dist = i;
		fill_file(file, lst, (*file)->value);
		(*lst)->tab[(*file)->value]->status = 1;
		//del_first_file(file);
		*file = (*file)->next;
	}
}

int			find_start(t_lst **lst, t_data *env, t_file **file)
{
	size_t	i;
	
	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->start == 1)
		{
			env->start = i;
			break ;
		}
		i++;
	}
	if ((fill_file(file, lst, i)) == -1)
		return (-1);
	(*lst)->tab[i]->dist = 0;
	(*lst)->tab[i]->status = 2;
	return (0);
}

int			algo_main(t_lst **lst, t_data *env)
{
	t_file	*file;

	printf("\n");
	if (!(file = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	if ((find_start(lst, env, &file)) == -1)
		return (-1);
	printf("L'algo du seigneur!\n");
	print_file(&file, lst);
//	bfs(&file, lst);
	printf("start est au maillon  %d\n", env->start);
	return (0);
}
