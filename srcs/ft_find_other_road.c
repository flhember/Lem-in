/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_other_road.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:52:59 by flhember          #+#    #+#             */
/*   Updated: 2019/12/06 17:30:51 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			pars_pipe_end(t_lst **lst, t_room *tmp, int i, int j)
{
	tmp = (*lst)->tab[j];
	while (tmp)
	{
		if (tmp->pos == (*lst)->tab[i]->pos && (*lst)->tab[j]->road == 0)
		{
			(*lst)->tab[j]->road = (*lst)->nb_road;
			printf("nbroad %d, %s -> ", (*lst)->nb_road, (*lst)->tab[j]->name);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int		other_road_bis(t_lst **lst, int ds, int i, int j)
{
//	printf("ds = %d, tab[j]->dist = %d\n", ds, (*lst)->tab[j]->dist);
	if (j == (*lst)->nb_room)
		return (0); // faire une ft check, soit intersiection avec un chemin donc remonter celui la, soit revenir en arriere jusqu'a un autre chemin. le rest ok
	if ((*lst)->tab[j]->dist != ds || (*lst)->tab[j]->road != 0)
		other_road_bis(lst, ds, i, ++j);
	if ((*lst)->tab[j]->dist == ds && (*lst)->tab[j]->road == 0)
	{
		if ((pars_pipe_end(lst, NULL, i, j)) != 0)
		{
			if ((*lst)->tab[j]->end == 1)
				return (1);
			else
				other_road_bis(lst, ++ds, j, 0);
		}
	}
	return (0);
}

//algo compris plus qu'a taper.
//A faire:
//	la condition du while avec le bfs, donc refaire bfs plus propre.
//	la fonction back up chemin/changer meilleur chemin si croisement.
//	ft a la con pour changer "nb road".
//	print chemin comme sujet.

int			other_road(t_lst **lst, t_data *env, t_file **file)
{
	int		i;
	int		ds;

	i = env->start;
	ds = 1;
	(*lst)->nb_road++;
	while () //tant que le bfs trouve des chemins
	{
		if ((other_road_bis(lst, ds, i, 0)) == -1)
			return (-1);
		(*lst)->nb_road++;
		printf("\n");
	}
	return (0);
}
