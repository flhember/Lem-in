/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chcoutur <chcoutur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:47:08 by chcoutur          #+#    #+#             */
/*   Updated: 2019/11/05 17:47:10 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char *ft_get_fd(int fd)
{
	char *line;
	int res;

	while ((res = get_next_line(fd, &line)) > 0)
		return (line);
	return (NULL);
}
