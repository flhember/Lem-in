/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charles <charles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:42:48 by flhember          #+#    #+#             */
/*   Updated: 2020/01/09 15:01:50 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

void		ft_reboot_for_oter(t_lst **lst)
{
	int		i;

	i = 0;
	(*lst)->nb_road = 0;
	while (i < (*lst)->nb_room)
	{
		(*lst)->tab[i]->road = 0;
		(*lst)->tab[i]->dist = 0;
		i++;
	}

}

int			find_end(t_lst **lst, t_data *env)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->end == 1)
		{
			env->end = i;
			return (0);
		}
		i++;
	}
	if (i >= env->nb_room)
		return (-1);
	return (-1);
}

int			find_start(t_lst **lst, t_data *env)
{
	size_t	i;

	i = 0;
	while (i < env->nb_room)
	{
		if ((*lst)->tab[i]->start == 1)
		{
			env->start = i;
			return (0);
		}
		i++;
	}
	if (i >= env->nb_room)
		return (-1);
	return (-1);
}

int			find_nb_pos(t_lst **lst, t_data *env)
{
	int		e;
	int		s;

	e = 0;
	s = 0;
	if ((find_start(lst, env) == -1) || (find_end(lst, env) == -1))
		return (-1);
	e = ft_lstsize_room(&(*lst)->tab[env->end]);
	s = ft_lstsize_room(&(*lst)->tab[env->start]);
	if (e <= s)
		env->nb_pos = e;
	else
		env->nb_pos = s;
	return (0);
}

int			algo_main(t_lst **lst, t_data *env)
{
	t_road	*road;

	road = NULL;		//LOUCHE!!
	(*lst)->nb_room = env->nb_room;
	if ((find_nb_pos(lst, env)) == -1)
		return (-1);
	if (best_road(lst, env) == -1)
		return (-1);
	printf("nb ant = %zu, nb best move = %d, pos possible = %d\n", env->nb_ants, (*lst)->nb_best_move
			, env->nb_pos);
	if ((int)env->nb_ants > (*lst)->nb_best_move)
	{
		printf("oui\n");
		ft_reboot_for_oter(lst);
		if (other_road(lst, env) == -1)
			return (-1);
	}
		printf("non\n");
	if (stock_road(lst, env) == -1)
		return (-1);

	return (0);
}
