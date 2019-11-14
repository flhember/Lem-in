/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:47:54 by flhember          #+#    #+#             */
/*   Updated: 2019/11/14 13:41:10 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "../libft/includes/libft.h"

# define ANTS		0b00001
# define START		0b00010
# define END		0b00100

# define ASTART		0b00001
# define AEND		0b00010
# define PSTART		0b00100
# define PEND		0b01000

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					start;
	int					end;
	struct s_room		*next;
}						t_room;

typedef struct			s_lst
{
	t_room				**tab;
	int					i_r;
}						t_lst;

typedef struct			s_stock
{
	char				*room;
	int					x;
	int					y;
	int					start;
	int					end;
	struct s_stock		*next;
}						t_stock;

typedef struct			s_data
{
	int					flags;
	int					se;
	int					nb_ants;
	int					nb_room;
}						t_data;

int						lem_in(void);
int						parsing_map(t_data *env, t_stock **lst);
int						creat_maillon(t_stock **lst, char *name, char *x,
		char *y);
int						stock_pipe(t_data *env, t_lst **lst, t_stock *pipe);
void					add_maillon_end(t_stock *room, t_stock *nw);
void					init_struct(t_data *env);
void					print_lst(t_stock **lst);
void					free_stock(t_stock **lst);
void					free_lst_adja(t_lst **lst, t_data *env);
void					stock_pipe(t_data *env, t_list **lst, t_stock *pipe);
t_stock					*creat_maillon_stock(void);
t_lst					*creat_adja_lst(t_stock **room, t_data *env);
t_lst					*parsing_main(t_data *env);

void					print_adja(t_lst **lst, t_data *env); // a tej


#endif
