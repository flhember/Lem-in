/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_use.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 12:02:54 by flhember          #+#    #+#             */
/*   Updated: 2020/02/05 12:26:35 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			find_nb_max(t_data *env)
{
	int		i;
	int		nb_max;

	i = 0;
	nb_max = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->nb_ant > nb_max)
			nb_max = env->road[i]->nb_ant;
		i++;
	}
	return (nb_max);
}

void		clean_status(t_lst **lst)
{
	int		i;

	i = 0;
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == 0)
			(*lst)->tab[i]->status = 0;
		i++;
	}
}

void		del_first_file(t_file **file)
{
	t_file	*tmp;

	tmp = *file;
	*file = (*file)->next;
	free(tmp);
}
