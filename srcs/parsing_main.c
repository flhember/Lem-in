/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:08:02 by flhember          #+#    #+#             */
/*   Updated: 2019/11/18 17:57:47 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lem_in.h>

/*void		print_map_room(t_stock *cpy)
{
	if (cpy->next)
		print_map_room(cpy->next);
	if (cpy->start)
		ft_printf("##start\n");
	if (cpy->end)
		ft_printf("##end\n");
	if ((cpy->pipe == 1 || cpy->com == 1) && cpy->room)
		ft_printf("%s\n", cpy->room);
	if (cpy->pipe == 0 && cpy->com == 0 && cpy->room)
		ft_printf("%s %d %d\n", cpy->room, cpy->x, cpy->y);

}

void		print_map(t_stock *lst, int nb_ant)
{
	t_stock	*cpy;

	cpy = lst;
	ft_printf("\nprint map:\n");
	ft_printf("%d\n", nb_ant);
	print_map_room(cpy);
}*/


t_lst		*parsing_main(t_data *env)
{
	t_lst	*lst;
	t_stock	*lst_tmp;

	lst = NULL;
	if (!(lst_tmp = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (NULL);
	if ((parsing_map(env, &lst_tmp) == -1) //|| (check_name(env, &lst_tmp) == -1 )
			|| (verif_pos(&lst_tmp) == -1))
	{
		free_stock(&lst_tmp);
		return (NULL);
	}
	ft_printf("toto\n");
	if (!(lst = creat_adja_lst(&lst_tmp, env))
			|| (stock_pipe(env, &lst, lst_tmp)) == -1)
	{
		if (lst)
			free_lst_adja(&lst, env);
		free_stock(&lst_tmp);
		return (NULL);
	}
//	print_map(lst_tmp, env->nb_ants);
	free_stock(&lst_tmp);
	return (lst);
}
