/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:40:53 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/27 13:46:56 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	check_size(t_content **content, int co, int li)
{
	int			lencol;
	int			i;
	int			index;
	int			total;
	t_content	*tmp;

	tmp = *content;
	total = 0;
	index = 0;
	tputs(tgetstr("ho", NULL), 0, &ft_inputchar);
	while (tmp && (i = -1))
	{
		lencol = 0;
		while (tmp && ++i < li - 1 && ++index)
		{
			if (ft_strlen(tmp->elem) > lencol)
				lencol = ft_strlen(tmp->elem);
			tmp->index = index - 1;
			tmp = tmp->next;
		}
		total += (lencol + 4);
		if (total - 4 > co)
			return (0);
	}
	return (1);
}

static void	moove(int x, int y, t_content *elem)
{
	elem->x = x;
	elem->y = y;
	tputs(tgoto(tgetstr("cm", NULL), x, y), 0, &ft_inputchar);
	if (elem->check)
		tputs(tgetstr("mr", NULL), 0, &ft_inputchar);
	ft_printf_fd(STDIN_FILENO, "%s", elem->elem);
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
}

int			display(t_content **content)
{
	int				lencol;
	int				i;
	int				total;
	struct winsize	screen;
	t_content		*tmp;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &screen);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	if (!check_size(content, screen.ws_col, screen.ws_row))
		return (0);
	total = 0;
	tmp = *content;
	while (tmp && (i = -1))
	{
		lencol = 0;
		while (tmp && ++i < screen.ws_row)
		{
			if (ft_strlen(tmp->elem) > lencol)
				lencol = ft_strlen(tmp->elem);
			moove(total, i, tmp);
			tmp = tmp->next;
		}
		total += (lencol + 4);
	}
	return (1);
}
