/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:24:05 by flhember          #+#    #+#             */
/*   Updated: 2019/11/08 15:41:47 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static t_list	*checkfd(t_list **list, const int fd, char **line)
{
	t_list	*tmp;
	char	buf[BUFF_SIZE + 1];

	tmp = *list;
	if (fd < 0 || line == NULL || BUFF_SIZE < 1 || (read(fd, buf, 0)) < 0)
		return (NULL);
	while (tmp)
	{
		if (fd == ((int)tmp->content_size))
		{
			if (!(tmp->content))
				return (NULL);
			return (tmp);
		}
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", fd);
	ft_lstadd(list, tmp);
	return (tmp);
}

static void		*read_fd(t_list **new, const int fd)
{
	int		size;
	char	buf[BUFF_SIZE + 1];
	t_list	*tmp;

	tmp = *new;
	size = 1;
	while ((ft_strchr(tmp->content, '\n') == 0) && size > 0)
	{
		if ((size = read(fd, buf, BUFF_SIZE)) < 0)
			return (0);
		buf[size] = '\0';
		tmp->content = ft_strjoinfree(tmp->content, buf, 1);
	}
	return (tmp->content);
}

static void		get_line(t_list **new, char **line)
{
	int		i;
	t_list	*tmp;
	char	*swap;

	tmp = *new;
	i = 0;
	while (((char *)tmp->content)[i] != '\n' && ((char *)tmp->content)[i])
		i++;
	*line = ft_strsub(tmp->content, 0, i);
	if (((char *)tmp->content)[i] == '\0')
		ft_strclr(tmp->content);
	else
	{
		swap = ft_strsub(tmp->content, i + 1, ft_strlen(tmp->content) - 1 - i);
		free(tmp->content);
		tmp->content = swap;
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*list = NULL;
	int				i;
	t_list			*new;

	i = 0;
	if (!(new = checkfd(&list, fd, line)))
		return (-1);
	*line = 0;
	if (!(new->content = read_fd(&new, fd)))
		return (0);
	if (((char*)(new->content))[i])
	{
		get_line(&new, line);
		return (1);
	}
	else
		ft_strclr(*line);
	return (0);
}
