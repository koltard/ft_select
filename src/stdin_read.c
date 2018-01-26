/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/20 15:36:11 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/26 08:42:47 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		print_color(int index, t_content **content)
{
	t_content	*tmp;

	tmp = *content;
	while (tmp->index != index)
		tmp = tmp->next;
	if (tmp->check)
		tputs(tgetstr("mr", NULL), 0, &ft_inputchar);
	else
		tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	ft_putstr_fd(tmp->elem, STDIN_FILENO);
	tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
}

void		print_under(int check, int index, t_content **content)
{
	t_content	*tmp;

	tmp = *content;
	while (tmp->index != index)
		tmp = tmp->next;
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

static int	escape_rmode(char *buf, t_content **content, t_content *tmp)
{
	int		ind;

	if (buf[1] == '[')
	{
		print_under(0, tmp->index, content);
		if (buf[2] == 'A')
			ind = go_up(content, tmp);
		if (buf[2] == 'B')
			ind = go_down(content, tmp);
		if (buf[2] == 'C')
			ind = go_right(content, tmp);
		if (buf[2] == 'D')
			ind = go_left(content, tmp);
		if (buf[2] == '3')
		{
			if ((ind = delete_elm(content, tmp->index)) == -1)
				return (-1);
			display(tgetnum("co"), tgetnum("li"), content);
			tputs(tgoto(tgetstr("cm", NULL), find_elm(content, ind)->x,
						find_elm(content, ind)->y), 0, &ft_inputchar);
		}
		print_under(1, ind, content);
		return (ind);
	}
	return (tmp->index);
}

static int	normal_rmode(char buf, t_content **content, t_content *tmp)
{
	int			ind;

	if (buf == 27)
		return (-2);
	if (buf == 10)
		return (-1);
	if (buf == 32)
		return (do_select(content, tmp->index));
	if (buf == 8 || buf == 127)
	{
		print_under(0, tmp->index, content);
		if ((ind = delete_elm(content, tmp->index)) == -1)
			return (-1);
		display(tgetnum("co"), tgetnum("li"), content);
		tputs(tgoto(tgetstr("cm", NULL), find_elm(content, ind)->x,
					find_elm(content, ind)->y), 0, &ft_inputchar);
		print_under(1, ind, content);
		return (ind);
	}
	return (tmp->index);
}

int			select_readtype(t_content **content)
{
	int			ret;
	int			pos;
	char		buf[8];
	t_content	*tmp;

	pos = 0;
	while ((ret = read(STDIN_FILENO, buf, 8)))
	{
		tmp = find_elm(content, pos);
		if (buf[0] == 27 && buf[1])
		{
			if ((pos = escape_rmode(buf, content, tmp)) < 0)
				break ;
		}
		else if ((pos = normal_rmode(buf[0], content, tmp)) < 0)
			break ;
		ft_bzero(&buf, 8);
	}
	if (pos == -2)
		free_list(content);
	ft_bzero(&buf, 8);
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	return (pos);
}
