/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:44:00 by flhember          #+#    #+#             */
/*   Updated: 2020/02/11 09:30:17 by charles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		free_blk_lst(t_blk_lst **blk)
{
	if ((*blk)->next)
		free_blk_lst(&(*blk)->next);
	free(*blk);
}


void		free_road_sol(t_data *env)
{
	int i;
	
	i = 0;
	(void)env;
	while (i < 4)
	{
		//free(&(env->road_sol[i]));
		i++;
	}
	//free(&env->road_sol);
}
