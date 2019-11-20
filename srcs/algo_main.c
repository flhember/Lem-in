/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:42:48 by flhember          #+#    #+#             */
/*   Updated: 2019/11/20 19:00:29 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_file(t_file **file)
{
	t_file *tmp;

	tmp = *file;
	while (tmp->next)
	{
		printf("%d -> ", tmp->value);	
		tmp = tmp->next;
	}
	printf("NULL\n");
}

int			add_file(t_file **file, int val)
{
	t_file	*new;

	new = NULL;
	printf("tete d'Os\n");
	if (!(new = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	new->value = val;
	new->next = *file;
	*file = new;
	return (0);
}

int			first_fill_file(t_file **file, t_lst **lst, int i)
{
	t_room *tmp;

	tmp = (*lst)->tab[i];
	while (tmp)
	{
		if (tmp->pos != i)
		{
			printf("%d %s\n", tmp->pos, tmp->name);
			if ((add_file(file, tmp->pos)) == -1)
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
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
	(*lst)->tab[i]->dist = 0;
	(*lst)->tab[i]->status = 1;
	if ((first_fill_file(file, lst, i)) == -1)
		return (-1);
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
	print_file(&file);
	printf("start est au maillon  %d\n", env->start);
	return (0);
}
