/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:08:47 by flhember          #+#    #+#             */
/*   Updated: 2019/12/02 16:13:53 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		free_stock(t_stock **lst)
{
	if ((*lst)->next)
		free_stock(&(*lst)->next);
	ft_strdel(&(*lst)->room);
	free(*lst);
}

void		free_file(t_file **file)
{
	if ((*file)->next)
		free_file(&(*file)->next);
	free(*file);
}

void		free_lst_tab(t_room **lst)
{
	if ((*lst)->next)
		free_lst_tab(&(*lst)->next);
	ft_strdel(&(*lst)->name);
	free(*lst);
}

void		free_lst_adja(t_lst **lst, t_data *env)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->next)
			free_lst_tab(&(*lst)->tab[i]);
		else
		{
			ft_strdel(&(*lst)->tab[i]->name);
			free((*lst)->tab[i]);
		}
		i++;
	}
	i = 0;
	free((*lst)->tab);
	free(*lst);
}
