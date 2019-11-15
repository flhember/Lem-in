/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:08:02 by flhember          #+#    #+#             */
/*   Updated: 2019/11/15 20:42:18 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

static int	check_this(t_stock **lst, int x, int y, int i)
{
	int		j;
	t_stock *cpy;

	j = 0;
	cpy = *lst;
	while (cpy)
	{
		if (cpy->pipe == 0 && j != i && cpy->x == x && cpy->y == y)
			return (-1);
		cpy = cpy->next;
		j++;
	}
	return (0);
}

int			verif_pos(t_stock **lst)
{
	int		i;
	t_stock *cpy;

	i = 0;
	cpy = *lst;
	while (cpy)
	{
		if (cpy->pipe == 0)
		{
			if (check_this(lst, cpy->x, cpy->y, i) == -1)
			{
				printf("error x/y, x = %d, y = %d, maillon name = [%s]\n",
						cpy->x, cpy->y, cpy->room);
				return (-1);
			}
		}
		i++;
		cpy = cpy->next;
	}
	return (0);
}

t_lst		*parsing_main(t_data *env)
{
	t_lst	*lst;
	t_stock	*lst_tmp;

	if (!(lst_tmp = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (NULL);
	if (parsing_map(env, &lst_tmp) == -1 || verif_pos(&lst_tmp) == -1)
	{
		free_stock(&lst_tmp);
		return (NULL);
	}
	if (!(lst = creat_adja_lst(&lst_tmp, env))
			|| (stock_pipe(env, &lst, lst_tmp)) == -1)
	{
		if (lst)
			free_lst_adja(&lst, env);
		free_stock(&lst_tmp);
		return (NULL);
	}
	free_stock(&lst_tmp);
	return (lst);
}
