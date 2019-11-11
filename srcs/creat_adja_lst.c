/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_adja_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:25:07 by flhember          #+#    #+#             */
/*   Updated: 2019/11/11 18:26:36 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void		fill_tab_room(t_stock **room_ptr, t_lst **lst, int i)
{
	int		j;
	t_stock	*room;

	j = 0;
	room = *room_ptr;
	while (j < i)
	{
		room = room->next;
		j++;
	}
	printf("test %s\n", room->room);
	(*lst)->tab[i]->name = room->room;
	(*lst)->tab[i]->x = room->x;
	(*lst)->tab[i]->y = room->y;
	(*lst)->tab[i]->start = 0;
	(*lst)->tab[i]->end = 0;
}

t_lst		*creat_adja_lst(t_stock **room, t_data *env)
{
	int		i;
	t_lst	*lst;

	i = 0;
	lst = NULL;
	printf("nb room = %d\n", env->nb_room);
	if (!(lst = (t_lst*)ft_memalloc(sizeof(t_lst))))
		return (NULL);
// Actuellement j'ai tres faim, je suis donc dans l'incapacite de continuer le code,
// note a moi meme, les list adja c'est pas facile, mais en vrais j'ai une piste la,
// mais j'ai trop faim a demain Florian, est ce que je parle tout seul ? oui. Si charles tu lis
// ca, Salut mec la forme? Je suis en exam la c'est plutot cool et j'ai surement encors faim
// J'ai toujours faim vers 11h.
	if (!(lst->tab = ft_memalloc(sizeof(t_room) * (env->nb_room + 1))))
		return (NULL);
	//lst->tab[env->nb_room] = NULL;

	while (i < env->nb_room)
	{
		fill_tab_room(room, &lst, i);
		i++;
	}
	return (lst);
}
