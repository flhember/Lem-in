/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:47:54 by flhember          #+#    #+#             */
/*   Updated: 2019/11/07 13:27:14 by chcoutur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "../libft/includes/libft.h"

# define ANTS		0b00001
# define START		0b00010
# define END		0b00100
# define RSTART		0b01000
# define REND		0b10000

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					start;
	int					end;
	struct s_room		*next;
	struct s_room		*prev;
}						t_room;

typedef struct			s_data
{
	int					flags;
	int					nb_ants;
}						t_data;

int						lem_in(void);
int						parsing_map(t_data *env, t_room *map);
void					init_struct(t_data *env);
void					init_lst(t_room *map);

#endif
