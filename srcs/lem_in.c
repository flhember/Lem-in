/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:08:59 by flhember          #+#    #+#             */
/*   Updated: 2020/02/06 15:20:47 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		lem_in(void)
{
	t_data		env;
	t_lst		*lst;

	lst = NULL;
	init_struct(&env);
	if (!(lst = parsing_main(&env)))
	{
		ft_putstr_fd("ERROR\n", 2);
		return (-1);
	}
	if ((algo_main(&lst, &env) == -1))
	{
		free_lst_adja(&lst, &env);
		return (-1);
	}
	sort_road(&env);
//	print_res(&env);
	free_road_adja(&env, lst->malloc_start);
	free_lst_adja(&lst, &env);
	return (0);
}
