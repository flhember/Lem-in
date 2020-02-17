/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:08:02 by flhember          #+#    #+#             */
/*   Updated: 2020/02/17 16:20:03 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			print_map(t_stock *lst_s, int nb_ant)
{
	t_stock	*cpy;

	cpy = lst_s;
	ft_printf("%d\n", nb_ant);
	while (cpy->next)
		cpy = cpy->next;
	while (cpy)
	{
		if (cpy->start)
			ft_printf("##start\n");
		if (cpy->end)
			ft_printf("##end\n");
		if ((cpy->pipe == 1 || cpy->com == 1) && cpy->room)
			ft_printf("%s\n", cpy->room);
		if (cpy->pipe == 0 && cpy->com == 0 && cpy->room)
			ft_printf("%s %d %d\n", cpy->room, cpy->x, cpy->y);
		cpy = cpy->prev;
	}
	return (0);
}

t_lst		*parsing_main(t_data *env, t_stock **lst_tmp)
{
	t_lst	*lst;

	lst = NULL;
	if ((parsing_map(env, lst_tmp) == -1)
			|| (verif_pos(lst_tmp) == -1))
		return (NULL);
	if ((!(lst = creat_adja_lst(lst_tmp, env, 0))
				|| (check_name(env, &lst) == -1)
				|| (stock_pipe(env, &lst, *lst_tmp)) == -1))
	{
		if (lst)
			free_lst_adja(&lst, env);
		return (NULL);
	}
	if ((find_nb_pos(&lst, env)) == -1)
	{
		if (lst)
			free_lst_adja(&lst, env);
		return (NULL);
	}
	return (lst);
}
