/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_other_road.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:52:59 by flhember          #+#    #+#             */
/*   Updated: 2019/12/07 18:57:44 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		change_road(t_lst **lst, int road, int new_road)
{
	int		i;

	i = 0;
	printf("je passe\n");
	while (i < (*lst)->nb_room)
	{
		if ((*lst)->tab[i]->road == new_road)
			(*lst)->tab[i]->road = 0;
		if ((*lst)->tab[i]->road == road)
			(*lst)->tab[i]->road = new_road;
		i++;
	}
	(*lst)->tab[(*lst)->cross]->road = new_road;
	(*lst)->nb_road = new_road;
}
int			verif_cross(t_lst **lst, int i)
{
	int		cmp;
	t_room	*tmp;
	int		cross;

	cmp = 0;
	cross = 0;
	tmp = (*lst)->tab[i];
	while (tmp)
	{
		if (tmp->pos != i)
		{
			if ((*lst)->tab[tmp->pos]->road == 1)
			{
				cross = 1;
				(*lst)->cross = tmp->pos;
			}
			else if ((*lst)->tab[tmp->pos]->road != (*lst)->nb_road)
				cmp++;
		}
		tmp = tmp->next;
	}
	printf("pour %s , cmp = %d, cross = %d\n", (*lst)->tab[i]->name, cmp, cross);
	if (cmp == 0 && cross == 1)
		return (1);
	return (-1);
}

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
	if (j == (*lst)->nb_room)
	{
		if (verif_cross(lst, i) == -1)
			return (-1);
		change_road(lst, (*lst)->nb_road, (*lst)->tab[(*lst)->cross]->road);
		j = 0;
		return (0);
	}
	else if ((*lst)->tab[j]->dist != ds || (*lst)->tab[j]->road != 0 || (*lst)->tab[j]->start == 1)
		other_road_bis(lst, ds, i, ++j);		// regler les retours
	else if ((*lst)->tab[j]->dist == ds && (*lst)->tab[j]->road == 0)
	{
		if ((pars_pipe_end(lst, NULL, i, j)) != 0)
		{
			if ((*lst)->tab[j]->end == 1)
				return (1);
			else
				other_road_bis(lst, ++ds, j, 0); // regler les retours
		//			other_road_bis(lst, --ds, i, ++j);
		}
		else
			other_road_bis(lst, ds, i, ++j);
	}
	return (0);
}

//algo compris plus qu'a taper.
//A faire:
//	la condition du while avec le bfs, donc refaire bfs plus propre. OK
//	la fonction back up chemin/changer meilleur chemin si croisement. OK
//	regler les retour de la fonction recursif
//	faire une ft check road (si pas de end ->del) + si la maillon du end et marque par la road la mettre a 0
//	ft a la con pour changer "nb road".
//	print chemin comme sujet.

void		print_road(t_lst **lst)
{
	int		i;
	int		j;

	i = 1;
	while (i < (*lst)->nb_road)
	{
		j = 0;
		ft_printf("ROAD %d :\n", i);
		while (j < (*lst)->nb_room)
		{
			if ((*lst)->tab[j]->road == i)
				ft_printf("%s -> ", (*lst)->tab[j]->name);
			j++;
		}
		printf("\n");
		i++;
	}
}

int			other_road(t_lst **lst, t_data *env)
{
	int		i;
	int		ds;
	int c = 0;

	i = env->start;
	ds = 1;
	(*lst)->nb_road++;
	while (bfs(env, lst) == 0)
	{
		if ((other_road_bis(lst, ds, i, 0)) == 0)
		{
			printf("ah oui oui\n");
			print_adja(lst, env);
		}
		(*lst)->nb_road++;
		printf("\n");
		c++;
	}
	print_road(lst);
	return (0);
}
