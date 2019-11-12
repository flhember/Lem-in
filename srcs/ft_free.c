/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:08:47 by flhember          #+#    #+#             */
/*   Updated: 2019/11/12 17:25:26 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		free_stock(t_stock **lst)
{
	if ((*lst)->next)
		free_stock(&(*lst)->next);
	ft_strdel(&(*lst)->room);
	free(*lst);
}

void		free_lst_adja(t_lst **lst, t_data *env)
{
	int		i;

/*	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i])

		i++;
	}*/
	i = 0;
	while (i < env->nb_room)
	{
		free((*lst)->tab[i]);
		i++;
	}
	free((*lst)->tab);
	free(*lst);
}
