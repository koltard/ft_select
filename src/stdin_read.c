/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:36:11 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/24 07:55:06 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		underline(int check, t_content *content)
{
	if (ft_tabchr(content->select, content->current[content->index]))
		tputs(tgetstr("mr", NULL), 0, ft_putchar);
	if (check)
		tputs(tgetstr("us", NULL), 0, ft_putchar);
	else
		tputs(tgetstr("ue", NULL), 0, ft_putchar);
	ft_putstr_fd(content->current[content->index], STDIN_FILENO);
	tputs(tgetstr("me", NULL), 0, ft_putchar);
	tputs(tgoto(tgetstr("cm", NULL), content->x, content->y), 0, ft_putchar);
}

static int	escape_rmode(char *buf, t_content *content)
{
	if (buf[1] == '[')
	{
		underline(0, content);
		if (buf[2] == 'A' && content->len > 1)
			go_up(content);
		if (buf[2] == 'B' && content->len > 1)
			go_down(content);
		if (buf[2] == 'C' && content->len > 1)
			go_right(content);
		if (buf[2] == 'D' && content->len > 1)
			go_left(content);
		underline(1, content);
		if (buf[2] == '3' && buf[3] == '4')
			;//DO CURRENT DEL (PRINTING IS SHITTY)
	}
	return (1);
}

static int	delete_elm(t_content *content)
{
	if (!(content->current = delete_tab(content->current,
					content->current[content->index])))
		return (0);
	content->len--;
	display(tgetnum("co"), tgetnum("li"), content);
	return (1);
}

static int	normal_rmode(char buf, t_content *content)
{
	int		i;

	i = -1;
	if (buf == 27)
	{
		if (content->select)
		{
			while (content->select[++i])
				ft_strdel(&content->select[i]);
			ft_memdel((void **)&content->select);
		}
		return (0);
	}
	if (buf == 26)//JOB MUST BE HANDLED CORRECTLY
		kill(0, SIGTSTP);
	if (buf == 10)
		return (0);
	if (buf == 32)
		do_select(content);
	if (buf == 8 || buf == 127)
		if (!delete_elm(content))
			return (0);
	return (1);
}

void		select_readtype(t_content *content)
{
	int		ret;
	char	buf[4];

	while ((ret = read(STDIN_FILENO, buf, 3)))
	{
		if (buf[0] == 27 && buf[1])
		{
			if (!(escape_rmode(buf, content)))
				break ;
		}
		else
		{
			if (!(normal_rmode(buf[0], content)))
				break ;
		}
		ft_bzero(&buf, 4);
	}
	tputs(tgetstr("me", NULL), 0, ft_putchar);
}
