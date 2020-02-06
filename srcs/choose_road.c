/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_road.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:02:17 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/03 16:58:13 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int		lstfail_size(t_fail *fail, int id)
{
	t_fail *tmp;
	int i;
	i = 0;
	id++;
	tmp = fail;
	//ft_printf("Liste id pour chemin %d:\n", id);
	while (tmp)
	{
//		ft_printf("%d ", tmp->id);
		if (tmp->id != -1)
			i++;
		tmp = tmp->next;
	}
//	ft_printf(" -> %d col\n", i);
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
//		ft_printf("Del %d sur %d state = %d | %d a %d col\n", to_del, i, env->road[i]->state, to_del, env->road[to_del]->col);
		if (i != to_del && env->road[i]->state <= -1 && env->road[i]->state != -3)
		{
			tmp = env->road[i]->f_road;
			back = tmp;
			while (tmp)
			{
				if (tmp->id == to_del)
				{
					ft_printf("\t\tsupression chemin %d sur chemin [%d]->%d col\n",to_del, i, env->road[i]->col);
					env->road[i]->col--;
					tmp->id = -1;
//					ft_printf("break\n");
					break ;
				}
				tmp = tmp->next;
			}
			env->road[i]->f_road = back;
//			ft_printf("retour breakk\n");
			if (lstfail_size(env->road[i]->f_road, i) == 0)
			{
//				ft_printf("\t\t==> Set chemin %d a etat 0\n", i);
				env->road[i]->col = 0;
				env->road[i]->state = 0;
			}
		}
		i++;
	}
}

/*
 * Je chope l'id de celui qui a le plus de croisements et apres l'avoir choper, dans choose_road je 
 * le met en statut -2, comme ca quand je rapelle la fonction je retraite pas le chemin ayant le plus de croisements
 * je prend celui qui en a moins, et ainsi de suite
 */

int		get_id_max(t_data *env)
{
	int max;
	int i;

	i = 0;
	max = i;
	while (i < env->nb_road_f)
	{
	//	ft_printf("Chemin [%d] statut -> [%d] || %d col\n", i, env->road[i]->state, env->road[i]->col);
		//if (env->road[max]->col < env->road[i]->col && env->road[i]->state != -2 && env->road[i]->col > 0)
		if (env->road[i]->col > env->road[max]->col && env->road[i]->state == -2)
			max = i;
		i++;
	}
//	if (max == 0 && env->road[max]->state == -2)
//		return (-1);
//	ft_printf("\t\t\t\tstatut de %d = [%d] suppose -2\n", max, env->road[max]->state);
	return (max);
}

/*
 * Ici je check combien j'ai de chemins avec plus de 1 croisements 
*/
/*
int		get_col_sup(t_data *env)
{
	int i;
	int col_sup;

	i = 0;
	col_sup = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->col > 2)
		{
			env->road[i]->state = -3;
//			ft_printf("Chemin %d col : %d col\n", i, env->road[i]->col);
			col_sup++;
		}
		i++;
	}
	return (col_sup);
}*/
/*
void print_road_failed(t_data *env, int id)
{
	t_fail *fail;
	int i;

	i = 0;
	fail = env->road[id]->f_road;
	ft_printf("Pour chemin %d :\n", id);
	while (fail)
	{
		ft_printf("%d ", fail->id);
		fail = fail->next;
	}
	ft_printf("\n");
}
*/

void	update_state(t_data *env)
{
	int i;

	i = 0;
	while (i < env->nb_road_f && env->road[i]->state != -3)
	{
		if (env->road[i]->col == 0)
			env->road[i]->state = 0;
		else if (env->road[i]->col == 1)
			env->road[i]->state = -1;
		else
			env->road[i]->state = -2;
		i++;
	}

}

int check_fail(t_data *env, int id)
{
	int i;
	t_fail *fail;

	i = 0;
	while (i < id)
	{
		fail = env->road[i]->f_road;
		while (fail)
		{
			if (fail->id == id)
			{
//				ft_printf("Fail : [%d] avec [%d]\n", fail->id, id);
				return (0);
			}
			fail = fail->next;
		}
		i++;
	}
	return (1);
}

int		get_ok(t_data *env)
{
	int i;
	int safe;

	i = 0;
	safe = 0;
	while (i < env->nb_road_f)
	{
		if (check_fail(env, i) == 1)
		{
			ft_printf("Chemin %d est OK\n", i);
			env->road[i]->state = 1;
			safe++;
		}
		else
			env->road[i]->state = -1;
		i++;
	}
	return (safe);
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
	int i;
	int j;
	int ok;
	//	t_fail *fail;
//	t_road *tmp;
	//update_state(env);
//	while (i < col_sup)
//	tmp = calcul_cost(env, i);
	ok = get_ok(env);
	ft_printf("%d chemins OK\n", ok);
	/*while (i < env->nb_road_f)
	{
	//	id_max = get_id_max(env);
	//	ft_printf("ID MAX = %d\n", id_max);
	//	if (env->road[id_max]->col == 0)
	//		break ;
		
		
		if (env->road[i]->state != 0)
		{
			ft_printf("Suppression du chemin %d\n", i);
//			print_road_failed(env, id_max);
			del_queue(env, i);
			env->road[i]->state = -3;
	//		update_state(env);
	//		ft_printf("Apres supp chemin %d state = %d\n", i, env->road[i]->state);
		}
		
		i++;
	}*/
	if (!(env->road_sol = ft_memalloc(sizeof(int) * ok)))
		return (-1);
	i = 0;
	j = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == 1)
		{
			env->road_sol[j] = i;
			j++;
		}
		i++;
	}
	env->nb_road_f = j;
	return (1);
}
