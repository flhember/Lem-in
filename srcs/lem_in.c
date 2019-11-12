/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:08:59 by flhember          #+#    #+#             */
/*   Updated: 2019/11/12 12:48:59 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		lem_in(void)
{
	t_data		env;
	t_stock		*lst_tmp;
	t_lst		*lst;

	init_struct(&env);
	if (!(lst_tmp = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (-1);
	if (parsing_map(&env, &lst_tmp) == -1)
		return (-1);
	lst = creat_adja_lst(&lst_tmp, &env);
	return (0);
}
