/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:08:59 by flhember          #+#    #+#             */
/*   Updated: 2019/11/08 17:09:55 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		lem_in(void)
{
	t_data		env;
	t_mark		lst;

	init_struct(&env);
	init_lst(&lst);
	if (parsing_map(&env, &lst) == -1)
		return (-1);
	return (0);
}
