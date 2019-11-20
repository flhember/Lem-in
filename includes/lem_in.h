/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:47:54 by flhember          #+#    #+#             */
/*   Updated: 2019/11/20 19:00:33 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

# define ANTS		0b00001
# define START		0b00010
# define END		0b00100

# define ASTART		0b00001
# define AEND		0b00010
# define PSTART		0b00100
# define PEND		0b01000
# define PIPE		0b10000

typedef struct			s_file
{
	int					value;
	struct s_file		*next;
}						t_file;

typedef struct			s_room
{
	int					pos;
	char				*name;
	int					dist;
	int					status;
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
	int					pipe;
	int					com;
	struct s_stock		*next;
}						t_stock;

typedef struct			s_data
{
	int					flags;
	int					se;
	int					start;
	size_t				nb_ants;
	size_t				nb_room;
}						t_data;

int						lem_in(void);
int						parsing_map(t_data *env, t_stock **lst);
int						creat_maillon(t_stock **lst, char *name, char *x,
		char *y);
int						stock_pipe(t_data *env, t_lst **lst, t_stock *pipe);
void					add_maillon_end(t_stock *room, t_stock *nw);
int						add_flag(t_data *env, int flag);
int						check_nb_ants(char *str, t_data *env);
int						nb_split(char **tab);
int						check_valid_room(char *str, t_data *env,
		t_stock(**lst));
void					init_struct(t_data *env);
void					print_lst(t_stock **lst);
void					free_stock(t_stock **lst);
void					free_lst_adja(t_lst **lst, t_data *env);
t_stock					*creat_maillon_stock(void);
t_lst					*creat_adja_lst(t_stock **room, t_data *env);
t_lst					*parsing_main(t_data *env);
size_t					ft_lstsize(t_stock **room);
void					print_adja(t_lst **lst, t_data *env); // a tej
void					print_lst_adja(t_lst **lst, t_data *env); // a tej
int						check_name(t_data *env, t_stock **room);
int						verif_pos(t_stock **lst);
int						algo_main(t_lst **lst, t_data *env);

#endif
