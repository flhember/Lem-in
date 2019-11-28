# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flhember <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 17:41:02 by flhember          #+#    #+#              #
#    Updated: 2019/11/28 17:00:49 by chcoutur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
COMP = clang
FLAGS = -g3 -Wall -Wextra -Werror

#-----------------------------------------SRC/INC-------------------------------#

SRC_FILES = main.c lem_in.c parsing_map.c init_struct.c ft_lst_stock.c 	\
			creat_adja_lst.c ft_free.c parsing_main.c parsing_map_sec.c \
			ft_stock_pipe.c ft_lstsize.c check_name.c verif_pos.c		\
			algo_main.c ft_bfs.c
INC = lem_in.h

#---------------------------------------PATH/FILES-------------------------------#

SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
LIB_PATH = ./libft/
INC_PATH = ./includes/

LIB_FILES = libft.a
LIB = $(addprefix $(LIB_PATH), $(LIB_FILES))
LIB_HEADER = $(addprefix $(LIB_PATH), $(INC_PATH))

INC_FILES = $(addprefix $(INC_PATH), $(INC))
OBJ_FILES = $(SRC_FILES:.c=.o)
	OBJ_EXEC = $(addprefix $(OBJ_PATH), $(OBJ_FILES))

#------------------------------------------RULES--------------------------------#

all: $(NAME)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(FLAGS) -c -I $(INC_PATH) -I$(LIB_HEADER) $< -o $@
	echo "\033[40mCompilation of \033[1m$(notdir $<)\033[0m \033[32mdone.\033[0m"

$(LIB): .FORCE
	make -C $(LIB_PATH)

$(NAME): $(INC_FILES) $(LIB) $(OBJ_PATH) $(OBJ_EXEC)
	$(CC) $(FLAGS) $(OBJ_EXEC) $(LIB) -o $(NAME) -I $(INC_PATH) -I $(LIB_HEADER)
	echo "\033[1;32m$(notdir $(NAME))\033[1;0m\033[32m created.\033[0m"

clean:
	/bin/rm -rf $(OBJ_PATH)
	make clean -C $(LIB_PATH)
	echo "\033[31mObjects files of \033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	/bin/rm -rf $(NAME)
	make fclean -C $(LIB_PATH)
	echo "\033[1;31m$(notdir $(NAME))\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.SILENT:
.FORCE:
.PHONY: clean, fclean, all, re
