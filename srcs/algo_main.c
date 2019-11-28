/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:42:48 by flhember          #+#    #+#             */
/*   Updated: 2019/11/28 10:21:41 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		print_file(t_file **file, t_lst **lst)
{
	t_file *tmp;

	tmp = *file;

	while (tmp->next)
	{
		ft_printf("[%d -> %s] -> ", tmp->value, (*lst)->tab[tmp->value]->name);
		//ft_printf("[%d -> ] -> ", tmp->value);
		tmp = tmp->next;
	}
	printf("NULL\n");
}

int			find_end(t_lst **lst, t_data *env)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->end == 1)
			return (i);
		i++;
	}
	return (-1);
}

int			good_road(t_lst **lst, t_data *env)
{
	int		i;
	size_t	j;
	int		ds;
	t_room 	*tmp;

	tmp = NULL;
	if (((i = find_end(lst, env)) == -1))
		return (-1);
	ds = (*lst)->tab[i]->dist;
	while (ds >= 0)
	{
		printf("\n %s -> %d ", (*lst)->tab[i]->name, ds);
		ds--;
		j = 0;
		while (j < env->nb_room)
		{
			if ((*lst)->tab[j]->dist == ds)
			{
				tmp = (*lst)->tab[j];
				while (tmp)
				{
					if (tmp->pos == (*lst)->tab[i]->pos)
					{
						i = j;
						j = env->nb_room + 2;
					}
					tmp = tmp->next;
				}
			}
			j++;
		}
	}
	printf("\n %s -> %d ->", (*lst)->tab[i]->name, ds);
	return (0);
}

//Yo, le bfs marche (On a la distance de chaque room au start)
//La ft good road retrace le meilleur chemin(d'apres mes test ca marche), tu print ont rend lundi?
//Non je deconne, en vrais je pense c'est trop simple il vas forcement y avoir un probleme,
//To do list:
//-stocker le chemin (list chainee?)
//-retrouver la formule ou demander a yohann (formie 1 ou plusieur chemin?)
//-(La j'ai peur de cette etape) trouver d'autre chemin si besoin
//-Faire les print final
//-corriger
//Ouai ouai ez lem_in bonne journee chef !

//ps: en vrais l'algo est nul je crois il boucle sur la map du sujet t(-.-t)
int			algo_main(t_lst **lst, t_data *env)
{
	t_file	*file;

	if (!(file = (t_file*)ft_memalloc(sizeof(t_file))))
		return (-1);
	if ((find_start(lst, env, &file)) == -1)
		return (-1);
	bfs(&file, lst);
	good_road(lst, env);
	print_file(&file, lst);
	free_file(&file);
	return (0);
}
