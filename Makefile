# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/18 14:27:11 by kyazdani          #+#    #+#              #
#    Updated: 2018/01/25 11:40:07 by kyazdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

CC = gcc 

SRCS = main.c init_attrs.c init_terms.c stdin_read.c display.c mount_list.c\
	   moove.c do_select.c

# libft
LIBINC = ./libft
INC += -I $(LIBINC)/includes

# ft_select
INCLUDES = ./includes/ 
INC += -I $(INCLUDES)

# Path ft_select srcs
PATHFS = ./src/

# flags
FLAGS = -Wall -Wextra

ifneq ($(NOERR),yes)
FLAGS += -Werror
endif

ifeq ($(DEV),yes)
FLAGS += -g
endif

ifeq ($(SAN),yes)
FLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

# termcap linker
TERMS = -ltermcap

# libft.a
LIB = ./libft/libft.a

OBJ = $(addprefix $(PATHFS), $(SRCS:%.c=%.o))

all : $(NAME)

$(NAME) : makelib $(OBJ)
		@$(CC) $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(LIB) $(TERMS)
		@echo "\033[35m***** done *****\033[0m"

%.o:%.c $(INCLUDES)
		@$(CC) $(FLAGS) $(INC) -o $@ -c $<
		@echo "\033[33m [$@] > compiled\033[0m"

makelib :
		@make -C $(LIBINC) NOERR=$(NOERR) DEV=$(DEV) SAN=$(SAN)

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
