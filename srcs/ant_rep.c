/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_rep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 15:20:19 by flhember          #+#    #+#             */
/*   Updated: 2020/01/16 15:52:21 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			get_road_size(t_road *cpy)
{
	int		i;
	t_road	*tmp;

	i = 0;
	tmp = cpy;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	ft_printf("size = %d\n", i);
	return (i);
}

int			get_worse(int i)
{
	return (i);
}

int			get_actual(int i, t_data *env)
{
	t_road	*cpy;

	cpy = env->road[i];
	cpy->size = get_road_size(cpy);
	ft_printf("size_lst env->road[%d] = %d\n", cpy->size);
	i = 0;
	while (cpy)
	{
		cpy = cpy->next;
		i++;
	}
	return (i);
}

int			get_basic_val(int i, t_data *env)
{
	int		worse;
	int		actual;

	worse = get_worse(i);
	actual = get_actual(i, env);
	ft_printf("ROAD [%d] -> Actual = %d | Worse = %d || TOTAL = %d\n\n", i,
			actual, worse, (1 + (actual - worse)));
	return (1 + (actual - worse));
}

int			ant_rep(t_data *env)
{
	int		**tab;
	int		i;

	i = 0;
	ft_printf("Nombre chemins = [ %d ]\n", env->nb_road_f - 1);
	if (!(tab = malloc(sizeof(int*) * (env->nb_road_f - 1))))
		return (-1);
	while (i < (env->nb_road_f - 1))
	{
		if (!(tab[i] = malloc(sizeof(int) * 1)))
			return (-1);
		tab[i][0] = get_basic_val(i, env);
		i++;
	}
	i = 0;
	while (i < ((env)->nb_road_f - 1))
	{
		ft_printf("tab[%d][0] = [ %d ]\n", i, tab[i][0]);
		i++;
	}
	return (1);
}
