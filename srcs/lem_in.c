/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:08:59 by flhember          #+#    #+#             */
/*   Updated: 2020/01/07 13:54:48 by flhember         ###   ########.fr       */
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
		ft_printf("oh shit, here we go again\n");
//		while (1)
//			;
		return (-1);
	}
	if ((algo_main(&lst, &env) == -1))
		return (-1);
//	print_adja(&lst, &env);
	free_lst_adja(&lst, &env);
	return (0);
}
