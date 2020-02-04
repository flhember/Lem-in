/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_road.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:02:17 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/03 17:25:37 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		lstfail_size(t_fail *fail)
{
	t_fail *tmp;
	int i;

	i = 0;
	tmp = fail;
	while (tmp)
	{
		if (tmp->id != -1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

/*
 * Ici je regarde sur les chemins qui ont un statut a -1 (ca veut dire qu'ils y a 1 croisement seulement)
 * et dans leur liste f_road(structure t_fail) je met a moins -1 l'id to_del (l'id_max enfait)
 * Et je check si, sur mon chemin si sa liste fait 1, et que le seul id present est -1 c'est qu'il est bon
 * je le met donc a 0
 *
*/

void	del_queue(t_data *env, int to_del)
{
	t_fail *tmp;
	t_fail *back;
	int i;

	i = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == -1)
		{
			tmp = env->road[i]->f_road->next;
			back = tmp;
			while (tmp)
			{
				if (tmp->id == to_del)
				{
//					ft_printf("\t\tCol-- sur chemin [%d]\n", i);
					env->road[i]->col--;
					tmp->id = -1;
				}
				tmp = tmp->next;
			}
			env->road[i]->f_road = back;
			if ((lstfail_size(env->road[i]->f_road) == 1 && back->id == -1) || lstfail_size(back) == 0)
				env->road[i]->state = 0;
		}
		i++;
	}
}

/*
 * Je chope l'id de celui qui a le plus de croisements et apres l'avoir choper, dans choose_road je 
 * le met en statut -2, comme ca quand je rapelle la fonction je retraite pas le chemin ayant le plus de croisements
 * je prend celui qui en a moins, et ainsi de suite
 * */

int		get_id_max(t_data *env)
{
	int max;
	int i;

	i = 0;
	max = i;
	while (env->road[i])
	{
		if (env->road[max]->col < env->road[i]->col && env->road[i]->state != -2 && env->road[i]->col > 0)
			max = i;
		i++;
	}
//	if (max == 0 && env->road[max]->state == -2)
//		return (-1);
	return (max);
}

/*
 * Ici je check combien j'ai de chemins avec plus de 1 croisements 
*/
int		get_col_sup(t_data *env)
{
	int i;
	int col_sup;

	i = 0;
	col_sup = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->col > 1)
		{
	//		ft_printf("Ajout col_sup : %d col\n", env->road[i]->col);
			col_sup++;
		}
		i++;
	}
	return (col_sup);
}

/*
 * La ca devient un peu complexe mais tranquille en deux trois lignes ca s' explique
 * Avec choose_road:
 * - Je calcul combien j'ai de chemins avec plus de 1 collisons, c' est col_sup
 * qui stock ca
 * - Ensuite je boucle sur cette valeur col_sup, et je chope id_max, c'est l'ID ou j'ai le plus de collisions
 *   et j'enleve cette ID (del_queue) la ou il croise sur les autres chemins
 *   En bouclant ca me permet d'enlever les gros croisements et je met le chemin id_max en statut -2 (je ne vais pas l' utiliser)
 *	
*/ 

int		choose_road(t_data *env)
{
	int id_max;
	int i;
	int col_sup;

	t_fail *fail;
	t_road *tmp;
	i = 0;
	id_max = 0;
	col_sup = get_col_sup(env);
	if (col_sup == 0)
		return (1);
	while (i < col_sup)
	{
		id_max = get_id_max(env);
//		ft_printf("\t\t\t\tID_MAX = %d\n", id_max);
		if (env->road[id_max]->col > 1)
		{
			env->road[id_max]->state = -2;
			del_queue(env, id_max);
		}
	i++;
	}
	i = 0;
//	ft_printf("STATE chemin 0 = %d\n", env->road[0]->state);
//	ft_printf("i %d | total road %d\n", i, env->nb_road_f);
	while (i < env->nb_road_f)
	{
		tmp = env->road[i];
		if (tmp->state == -2)
		{
			fail = tmp->f_road;
			ft_printf("______________________");
			ft_printf("\nChemins [%d] -> KO pour %d collisions\n", i, env->road[i]->col);
			ft_printf("Avec chemins :");
			while (fail)
			{
				ft_printf("%d ", fail->id);
				fail = fail->next;
			}
			ft_printf("\n______________________\n\n");
		}
		else
			ft_printf("Chemin [%d] -> OK\n", i);
		i++;
	}
	return (1);
}
