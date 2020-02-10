/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb_ant_road.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:21:01 by flhember          #+#    #+#             */
/*   Updated: 2020/02/10 19:06:19 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_debug(t_data *env) //ouais ouais tu degages
{
	int		i;

	i = 0;
	while (i < env->road_sol[env->tab_choose][0])
	{
		printf("nb ants = %d\n",
				env->road[env->road_sol[env->tab_choose - 1][i]]->rep_ant);
		i++;
	}
}

void		nb_ant_road(t_data *env)
{
	int		i;
	size_t	nb_ants_tmp;

	ft_printf("TAB_CHOOSE 2 = %d\n", env->tab_choose);
	i = 0;
	nb_ants_tmp = env->nb_ants;
	ft_printf("env->road_sol = %d\n", env->road_sol[env->tab_choose][0]);
	while (i < env->road_sol[env->tab_choose][0])
	{
		env->road[env->road_sol[env->tab_choose - 1][i]]->rep_ant =
			env->road_sol[env->tab_choose][1] -
			env->road[env->road_sol[env->tab_choose - 1][i]]->size;
		nb_ants_tmp -= env->road[env->road_sol[env->tab_choose - 1][i]]->rep_ant;
		i++;
	}
	while (nb_ants_tmp > 0)
	{
		i = 0;
		while (i < env->road_sol[env->tab_choose][0])
		{
			env->road[env->road_sol[env->tab_choose - 1][i]]->rep_ant++;
			nb_ants_tmp--;
			if (nb_ants_tmp == 0)
				break ;
			i++;
		}
	}
	print_debug(env);
}
