/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:42:48 by flhember          #+#    #+#             */
/*   Updated: 2019/11/21 15:40:03 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*void		find_start(t_lst **lst, t_data *env)
{
	int		i;
	
	i = 0;
	while ((*lst)->tab[i]->start == 0)
	{
		i++;
		if ((*lst)->tab[i]->start == 1)
			env->start = i;
	}
}*/

int			algo_main(t_lst **lst, t_data *env)
{
	(void)lst;
//	find_start(lst, env);
	printf("start est au maillon = %d\n", env->start);
	return (0);
}
