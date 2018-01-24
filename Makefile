# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/18 14:27:11 by kyazdani          #+#    #+#              #
#    Updated: 2018/01/24 08:12:25 by kyazdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
CC = gcc 
SRCS = main.c init_attrs.c init_terms.c stdin_read.c display.c selection.c \
	   moove_vert.c moove_sides.c do_select.c
LIBINC = ./libft/includes/
INCLUDES = ./includes/ 
PATHFS = ./src/
FLAGS = -Wall -Werror -Wextra
TERMS = -ltermcap
LIB = ./libft/libft.a
OBJ = $(addprefix $(PATHFS), $(SRCS:%.c=%.o))

all : $(NAME)

$(NAME) : makelib $(OBJ)
		@$(CC) $(FLAGS) $(TERMS) -o $(NAME) $(OBJ) $(LIB) -I$(INCLUDES) -I$(LIBINC)
		@echo "\033[35m***** done *****\033[0m"

%.o:%.c $(INCLUDES)
		@$(CC) $(FLAGS) -o $@ -c $< -I$(INCLUDES) -I$(LIBINC)
		@echo "\033[33m [$@] > compiled\033[0m"

makelib :
		@make -C ./libft

clean : cleanlib
		@/bin/rm -rf $(OBJ)
		@echo "\033[31m--== objects trashed ==--\033[0m"

cleanlib :
		@make clean -C ./libft

fclean : fcleanlib clean
		@/bin/rm -f $(NAME)
		@echo "\033[033m--== binary trashed ==--\033[0m"

fcleanlib :
		@make fclean -C ./libft

re : fclean all

.PHONY : all clean fclean re
