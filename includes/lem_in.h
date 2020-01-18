/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:47:54 by flhember          #+#    #+#             */
/*   Updated: 2020/01/16 17:50:02 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"

# define ANTS		1
# define START		2
# define END		4

# define ASTART		1
# define AEND		2
# define PSTART		4
# define PEND		8
# define PIPE		16

typedef struct			s_road
{
	char				*name;
	int					nb_road;
	int					nb_cost;
	int					size;
	struct s_road		*next;
}						t_road;

typedef struct			s_file
{
	int					value;
	int					dist;
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
	int					road;
	int					print;
	struct s_room		*next;
}						t_room;

typedef struct			s_lst
{
	t_room				**tab;
	int					tmp_pos;
	int					cmp;
	int					pos_blk;
	int					nb_road;
	int					total_room;
	int					nb_best_move;
	int					nb_room;
	int					ret_bfs;
	int					cross;
	int					end;
	int					size_file;
}						t_lst;

typedef struct			s_stock
{
	char				*room;
	char				*room1;
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
	int					tmp_pos;
	int					flags;
	int					se;
	int					start;
	int					end;
	int					nb_pos;
	size_t				nb_ants;
	size_t				nb_room;
	int					nb_road_f;
	t_road				**road;
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
void					free_road_adja(t_data *env);
t_stock					*creat_maillon_stock(void);
t_lst					*creat_adja_lst(t_stock **room, t_data *env, size_t i);
t_lst					*parsing_main(t_data *env);
size_t					ft_lstsize_stock(t_stock **room);
size_t					ft_lstsize_room(t_room **room);
int						ft_lstsize_road(t_road **room);
void					print_adja(t_lst **lst, t_data *env); // a tej
void					print_lst_adja(t_lst **lst, t_data *env); // a tej
int						check_name(t_data *env, t_lst **lst);
int						verif_pos(t_stock **lst);
int						algo_main(t_lst **lst, t_data *env);
int						bfs(t_data *env, t_lst **lst, t_file *tmp);
int						bfs_best(t_data *env, t_lst **lst, t_file *tmp);
void					free_file(t_file **file);
int						best_road(t_lst **lst, t_data *env);
int						other_road(t_lst **lst, t_data *env);
int						print_road(t_lst **lst, t_data *env, t_room *tmp); // a tej ft test
void					del_first_file(t_file **file);
void					clean_status(t_lst **lst);
void					clean_dist(t_lst **lst);
void					change_road_bfs(t_lst **lst, int road);
void					reboot_nb_road(t_lst **lst);
int						stock_road(t_lst **lst, t_data *env);
int						stock_start_end(t_lst **lst, t_data *env);
int						block_bad_road(t_lst **lst, int i);
int						verif_back(t_lst **lst, int pos_blk, int i, int flag);
int						ant_rep(t_data *env);
int						check_cross(t_lst **lst, t_file **file, int i,
		int pos_blk);
int						check_cross_bis(t_lst **lst, t_file **file,
		int i, int pos_blk);
int						add_file(t_lst **lst, t_file **file, int val,
		int dis);

#endif
