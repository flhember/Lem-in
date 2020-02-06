/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rework_for_best.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:05:19 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/06 12:14:09 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		check_if_necessary(t_data *env)
{
	int i;

	i = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state < 0)
			return (1);
		else
			i++;
	}
	return (0);
}

int rework_for_best (t_data *env)
{
	if (check_if_necessary(env) == 1)
	{
		ft_printf("C'est pas finit\n");
	}
	return (1);
}
