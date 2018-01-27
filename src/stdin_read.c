/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:36:11 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/27 16:24:42 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_module		*g_module;

void				print_color(t_content *tmp)
{
	if (tmp->check)
		tputs(tgetstr("mr", NULL), 0, &ft_inputchar);
	else
		tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	ft_putstr_fd(tmp->elem, STDIN_FILENO);
	tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
}

void				print_under(int check, t_content *tmp)
{
	if (tmp->check)
		tputs(tgetstr("mr", NULL), 0, &ft_inputchar);
	if (check)
		tputs(tgetstr("us", NULL), 0, &ft_inputchar);
	else
		tputs(tgetstr("ue", NULL), 0, &ft_inputchar);
	ft_putstr_fd(tmp->elem, STDIN_FILENO);
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
}

static t_content	*escape_rmode(char *buf, t_content **content,
					t_content *tmp)
{
	t_content	*elm;

	elm = tmp;
	if (buf[1] == '[')
	{
		print_under(0, tmp);
		if (buf[2] == 'A')
			elm = go_up(content, tmp);
		if (buf[2] == 'B')
			elm = go_down(content, tmp);
		if (buf[2] == 'C')
			elm = go_right(content, tmp);
		if (buf[2] == 'D')
			elm = go_left(content, tmp);
		if (buf[2] == '3')
		{
			if (!(elm = delete_elm(content, tmp)))
				return (NULL);
			display(content);
		}
		tputs(tgoto(tgetstr("cm", NULL), elm->x, elm->y), 0, &ft_inputchar);
		print_under(1, elm);
		g_module->current = elm->index;
	}
	return (elm);
}

static t_content	*normal_rmode(char buf, t_content **content, t_content *tmp)
{
	t_content	*elm;

	elm = tmp;
	print_under(0, tmp);
	if (buf == 27)
	{
		free_list(content);
		return (NULL);
	}
	if (buf == 10)
		return (NULL);
	if (buf == 32)
		elm = do_select(content, tmp);
	if (buf == 8 || buf == 127)
	{
		if (!(elm = delete_elm(content, tmp)))
			return (NULL);
		display(content);
		tputs(tgoto(tgetstr("cm", NULL), elm->x, elm->y), 0, &ft_inputchar);
	}
	print_under(1, elm);
	g_module->current = elm->index;
	return (elm);
}

int					select_readtype(t_content **content)
{
	int			ret;
	char		buf[8];
	t_content	*tmp;

	tmp = *content;
	print_under(1, tmp);
	while ((ret = read(STDIN_FILENO, buf, 8)))
	{
		while (!g_module->checked)
			;
		if (buf[0] == 27 && buf[1])
		{
			if (!(tmp = escape_rmode(buf, content, tmp)))
				break ;
		}
		else if (!(tmp = normal_rmode(buf[0], content, tmp)))
			break ;
		ft_bzero(&buf, 8);
	}
	ft_bzero(&buf, 8);
	return (0);
}
