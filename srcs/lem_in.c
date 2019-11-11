/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 18:08:59 by flhember          #+#    #+#             */
/*   Updated: 2019/11/11 18:27:14 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		lem_in(void)
{
	t_data		env;
	t_stock		*lst_tmp;
	t_lst		*lst;

	init_struct(&env);
	if (!(lst_tmp = (t_stock*)ft_memalloc(sizeof(t_stock))))
		return (-1);
	if (parsing_map(&env, &lst_tmp) == -1)
	{
		//Salut charles, tu vas bien?
		//Moi oui.
		//C'est bientot noel pense a faire ta liste pour le pere noel.
		//Appelle le 36303630 pour lui demander si tu a etais sage.
		//Alors j'ecris tout ca pour rien, oui, mais la suite est importante alors lis la.
		//Il faudra penser a free la struct t_stock pour eviter
		//les futur leaks.
		//Merci d'en prendre note,
		//Florian le meilleur alias florian.
		return (-1);
	}
	lst = creat_adja_lst(&lst_tmp, &env);
	return (0);
}
