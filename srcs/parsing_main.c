/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:08:02 by flhember          #+#    #+#             */
/*   Updated: 2019/11/15 12:57:39 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_lst		*parsing_main(t_data *env)
{
	t_lst	*lst;
	t_stock	*lst_tmp;
	
	if (!(lst_tmp = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (NULL);
	if (parsing_map(env, &lst_tmp) == -1)
	{
		free_stock(&lst_tmp);
		return (NULL);
	}
	lst = creat_adja_lst(&lst_tmp, env);
//	free_stock(&lst_tmp);

	if ((stock_pipe(env, &lst, lst_tmp)) == -1)
	{
		free_stock(&lst_tmp);
		return (NULL);
	}
	free_stock(&lst_tmp);
	return (lst);
}
