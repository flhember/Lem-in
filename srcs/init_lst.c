/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:04:55 by flhember          #+#    #+#             */
/*   Updated: 2019/11/05 15:44:39 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	add_link(t_room *map, t_room *new)
{
	new->next = NULL;
	new->prev = map;
	map->next = 
}


void	init_lst(t_room *map)
{
	map->name = NULL;
	map->next = NULL;
	map->prev = NULL;
}
