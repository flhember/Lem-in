/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_coord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:37:13 by chcoutur          #+#    #+#             */
/*   Updated: 2020/02/17 16:44:34 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_coord(char *str)
{
	int		ret;
	int		size;

	size = ft_strlen(str);
	if (size > 10)
		return (-1);
	if (size == 10 || size == 11)
	{
		if ((ret = ft_strcmp(str, "2147483647")) > 0)
			return (-1);
		if ((ret = ft_strcmp(str, "-2147483648")) > 0)
			return (-1);
	}
	return (1);
}
