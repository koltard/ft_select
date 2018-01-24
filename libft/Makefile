# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/24 17:49:45 by kyazdani          #+#    #+#              #
#    Updated: 2018/01/24 15:44:12 by kyazdani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc

# printf sources
SRC = ft_convert_str.c ft_handle_percent.c ft_flags.c ft_printf.c \
	  ft_str_parse.c ft_handle_d.c ft_handle_c.c ft_handle_base.c \
	  ft_handle_s.c ft_handle_base_2.c ft_str_join.c ft_handle_d_2.c \
	  ft_return_s.c ft_handle_binary.c ft_handle_f.c ft_flags_2.c \
	  ft_handle_c_2.c ft_colors.c ft_parse_brackets.c ft_ltoa.c \
	  ft_untoa.c ft_dtoa.c ft_ldtoa.c ft_printf_fd.c

# libft sources
LIBSRC = ft_strlen.c ft_strcspn.c ft_strdup.c ft_strndup.c ft_strcpy.c \
	ft_strncpy.c ft_strcmp.c ft_strncmp.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	ft_strstr.c ft_strnstr.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
	ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c \
	ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c \
	ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c \
	ft_itoa.c ft_itoa_base.c ft_putchar.c ft_putstr.c ft_addstr_tab.c \
	ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_tablen.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_freetab.c \
	ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_strstrchr.c ft_getopt.c\
	ft_lstmap.c ft_lst_push_back.c ft_lst_push_front.c ft_lst_count.c 

PATHPRINTF = srcs/printf/
PATHLIBFT = srcs/
INCLUDES = includes/
INC += -I $(INCLUDES)
LFLAGS = -Wall -Wextra

ifneq ($(NOERR),yes)
LFLAGS += -Werror
endif

ifeq ($(DEV),yes)
LFLAGS += -g
endif

ifeq ($(SAN),yes)
LFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

AR = ar rc
OBJ = $(addprefix $(PATHPRINTF), $(SRC:%.c=%.o))
LIBOBJ = $(addprefix $(PATHLIBFT), $(LIBSRC:%.c=%.o))

all : $(NAME)

$(NAME) : print $(OBJ) $(LIBOBJ)
	@$(AR) $(NAME) $(OBJ) $(LIBOBJ) 
	@ranlib $(NAME)
	@echo "\033[33m libft : ready \033[34m]\033[0m"

print :
	@echo "\033[34m[\c"

%.o:%.c $(INCLUDES)
	@$(CC) $(LFLAGS) $(INC) -o $@ -c $<
	@echo ">\c"

clean : 
	@/bin/rm -rf $(OBJ) 
	@/bin/rm -rf $(LIBOBJ)


fclean : clean
	@/bin/rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
