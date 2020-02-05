/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_road.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:10:53 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/05 16:06:56 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*
 * Je crois que je n'ai rien a expliquer haha
 */

void print_road_f(t_data *env)
{
	t_road *tmp;
	int i;

	i = 0;
	while (i < env->nb_road_f)
	{
		if (env->road[i]->state == 0)
		{
			tmp = env->road[i]->next;
			ft_printf("Chemin [%d] \n\n", i);
			while (tmp)
			{
				ft_printf("%s", tmp->name);
				if (tmp->next != NULL)
				{
					ft_printf(" ->");
				}
			tmp = tmp->next;
			}
		ft_printf("%20s%d\n\n", "| size = ", env->road[i]->size);
		ft_printf("\n");
		}
		i++;
	}
}

/*
 * linkfail c'est la suite de mark_fail, c' est ici que j'ajoute le maillon avec l' ID
 * sur le chemin
 */

int		link_fail(t_data *env, int i, int j)
{
	t_fail *road;
	t_fail *tmp;

	tmp = env->road[i]->f_road;
	if (!(road = ft_memalloc(sizeof(t_fail))))
		return (-1);
	road->id = j;
	road->next = NULL;
//	ft_printf("on met %d dans %d\n", j, i);
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = road;
	return (1);
}

/*
 * Mark_fail c' est mon poulain, si il y a un croisement elle va creer la liste
 * t_fail sur les deux chemins et ajouter le maillon avec l' ID du chemin
*/

void	print_link(t_data *env, int i, int j)
{
	t_fail *fail;

	fail = env->road[i]->f_road;
	j++;
	ft_printf("lien de %d :\n", i);
	while (fail)
	{
		ft_printf("%d ", fail->id);
		fail = fail->next;
	}
	ft_printf("\n");
}

void	mark_fail(t_data *env, int i, int j)
{
	if (env->road[i]->f_road == NULL)
	{
		if (!(env->road[i]->f_road = ft_memalloc(sizeof(t_fail))))
			return ;
		env->road[i]->f_road->id = j;
	}
	else
		link_fail(env, i, j);
	if (env->road[j]->f_road == NULL)
	{
		if (!(env->road[j]->f_road = ft_memalloc(sizeof(t_fail))))
			return ;
		env->road[j]->f_road->id = i;
	}
	else
		link_fail(env, j, i);
	env->road[i]->state = -1;
	env->road[j]->state = -1;
	env->road[i]->col++;
	env->road[j]->col++;
}

/*
 * La je check si A est pas deja marque par B
 * A quoi ca sert ? Bah imagine A fait 100 rooms et B en fait 2
 * Si la premiere room de B croise la premiere room de A, on s'en fout de 
 * ce qui va croiser apres, parceque j' en ai deja une 
 * C'est que fait find_id, si je check A et B je regarde si j'ai pas deja un croisement
*/

int find_id(t_data *env, int i, int j)
{
	t_fail *tmp;

	tmp = env->road[i]->f_road;
	while (tmp)
	{
		if (tmp->id == j)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
 *
 * Donc solve_cross il prend chaque chemins et check lequel croise
 * avec lequel
 * Si A croise sur B au moins une fois, dans A je vais mettre B et inversement
 * C'est mark_fail qui fait ca, sur une liste t_fail
 *
*/ 

int solve_cross(t_data *env)
{
	int i;
	int j;

	t_road *nex;
	t_road *act;
	i = 0;
	j = 1;
	while (i < env->nb_road_f - 1)
	{
		act = env->road[i]->next;
		while (act->next)
		{
			while (j < env->nb_road_f)
			{
			//	ft_printf("Comparaison %d avec %d\n", i, j);
				nex = env->road[j]->next;
				while (nex->next && find_id(env, i, j) == 0)
				{
					if (act->index == nex->index && find_id(env, i, j) == 0)
					{
						ft_printf("Chemin [%d] croise [%d] sur %s et %s\n",i, j, act->name, nex->name);
						mark_fail(env, i, j);
					}
					else
						nex = nex->next;
				}
				j++;
			}
			act = act->next;
			j = i + 1;
		}
		i++;
		j = i + 1;
	}
	
	
	
//	print_road_f(env);
	return (1);
}

/*
 *Okok mon pote la on rigole plus.
 *Sort road elle te sert a prendre les chemins que le bfs sort et 
 *tout mettre dans l'ordre (rien de ouf juste un tri a bulle)
 *
*/



int sort_road(t_data *env)
{
	int i;

	t_road *tmp;
	t_fail *fail;
	i = 0;
	tmp = NULL;
	env->nb_road_f--;
//	ft_printf("_____________________________\n\n\n\n\n");
//	ft_printf("nb_road = %d\n", env->nb_road_f);
	if (env->nb_road_f == 1)
		return (1);
	while (i < env->nb_road_f -1)
	{
		env->road[i]->state = 0;
		env->road[i]->col = 0;
		if (env->road[i]->size > env->road[i + 1]->size)
		{
			tmp = env->road[i];
			env->road[i] = env->road[i + 1];
			env->road[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
	
	i = 0;
	solve_cross(env);
	i = 0;
	while (i < env->nb_road_f)
	{
		tmp = env->road[i];
		if (tmp->state < 0)
		{
			fail = tmp->f_road;
			ft_printf("_____________________");
			ft_printf("\nChemin [%d] -> KO pour %d collisions\n size = %d", i, env->road[i]->col, env->road[i]->size);
			ft_printf("Avec chemins :");
			while (fail)
			{
				ft_printf("%d ", fail->id);
				fail = fail->next;
			}
			ft_printf("\n_____________________\n\n");
		}
		else
			ft_printf("Chemin [%d] -> OK size = %d\n", i, env->road[i]->size);
		i++;
	}

	choose_road(env);
	/*i = 0;
	while (i < env->nb_road_f)
	{
		tmp = env->road[i];
		if (tmp->state < 0)
		{
			fail = tmp->f_road->next;
			ft_printf("_____________________");
			ft_printf("\nChemin [%d] -> KO pour %d collisions state -> %d size = %d\n", i, env->road[i]->col, env->road[i]->state, env->road[i]->size);
			ft_printf("Avec chemins :");
			while (fail)
			{
				ft_printf("%d ", fail->id);
				fail = fail->next;
			}
			ft_printf("\n_____________________\n\n");
		}
		else
			ft_printf("Chemin [%d] -> OK\n", i);
		i++;
	}*/
ants_treat(env);
	//	ft_printf("\n\n\n");
//	print_road_f(env);
	return (1);

}
