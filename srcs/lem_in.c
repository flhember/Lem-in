/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:08:59 by flhember          #+#    #+#             */
/*   Updated: 2019/11/20 18:43:37 by flhember         ###   ########.fr       */
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
		return (-1);
	if (!(algo_main(&lst, &env)))
		return (-1);
	free_lst_adja(&lst, &env);
	return (0);
}
