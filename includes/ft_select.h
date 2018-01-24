/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:20:56 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/24 13:37:58 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <signal.h>
# include "libft.h"

int		g_display;

typedef struct		s_content
{
	int		x;
	int		y;
	int		len;
	int		index;
	char	**current;
	char	**select;
}					t_content;
/*
** init_attrs
*/
void	ft_cfmakeraw(struct termios *my_state);
void	ft_cfmakedefault(struct termios *my_state);
/*
** init_terms
*/
char	*get_ttyname(void);
int		init_termcaps(void);
/*
** mooves
*/
void	go_up(t_content *content);
void	go_down(t_content *content);
void	go_left(t_content *content);
void	go_right(t_content *content);
void	select_readtype(t_content *content);
int		handle_size(void);
void	display(int co, int li, t_content *content);
int		count_max_len(char **tabl, int li);
void	do_select(t_content *content);
void	underline(int check, t_content *content);
/*
** selection.c
*/
int		ft_tabchr(char **tabl, char *str);
char	**delete_tab(char **tabl, char *str);
char	**put_new_tab(char **tabl, char *str);
char	**cpy_av(char **str, int len);
#endif
