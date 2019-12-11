/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_road.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:48:26 by flhember          #+#    #+#             */
/*   Updated: 2019/12/10 16:48:43 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

int			print_road(t_lst **lst, t_data *env, t_room *tmp)
{
	int		i;
	int		pos;
	int		flag;

	i = 1;
	pos = 0;
	flag = 0;
	while (i < (*lst)->nb_road)
	{
		ft_printf("\nROAD %d: \n", i);
		pos = env->start;
		tmp = (*lst)->tab[pos];
		ft_printf("%s -> ", (*lst)->tab[pos]->name);
		while ((*lst)->tab[pos]->end == 0)
		{
			flag = 0;
			while (flag == 0)
			{
				if (tmp->pos != pos && (*lst)->tab[tmp->pos]->print == 0 && ((*lst)->tab[tmp->pos]->road == i || (*lst)->tab[tmp->pos]->end == 1))
				{
					flag = 1;
					pos = tmp->pos;
					if ((*lst)->tab[tmp->pos]->end == 0)
					{
						(*lst)->tab[pos]->print = 1;
						ft_printf("%s -> ", (*lst)->tab[pos]->name);
					}
					else if ((*lst)->tab[tmp->pos]->end == 1)
						ft_printf("%s", (*lst)->tab[pos]->name);
				}
				else
				{
					tmp = tmp->next;
					if (!tmp)
						return (0);
				}
			}
			tmp = (*lst)->tab[pos];
		}
		i++;
	}
	printf("\n");
	return (0);
}
