/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 10:53:48 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/17 12:21:56 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_free_tab_char(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_printf("Free de [%s]\n", str[i]);
		ft_strdel(&str[i]);
		i++;
	}
	free(str);
}
