/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:08:02 by flhember          #+#    #+#             */
/*   Updated: 2019/11/16 19:20:14 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

t_lst		*parsing_main(t_data *env)
{
	t_lst	*lst;
	t_stock	*lst_tmp;

	lst = NULL;
	if (!(lst_tmp = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (NULL);
	if ((parsing_map(env, &lst_tmp) == -1) || (check_name(env, &lst_tmp) == -1)
			|| (verif_pos(&lst_tmp) == -1))
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
