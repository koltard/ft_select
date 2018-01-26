/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:40:53 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/26 09:00:02 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	check_size(t_content **content, int co, int li)
{
	int			lencol;
	int			i;
	int			total;
	t_content	*tmp;

	tmp = *content;
	total = 0;
	tputs(tgetstr("ho", NULL), 0, &ft_inputchar);
	while (tmp && (i = -1))
	{
		if (total > co)
			return (0);
		while (tmp && ++i < li - 1 && !(lencol = 0))
		{
			if (ft_strlen(tmp->elem) > lencol)
				lencol = ft_strlen(tmp->elem);
			tputs(tgoto(tgetstr("cm", NULL), total, 0), 0, &ft_inputchar);
			tmp = tmp->next;
		}
		total += (lencol + 4);
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

int			display(int co, int li, t_content **content)
{
	int			lencol;
	int			i;
	int			index;
	int			total;
	t_content	*tmp;

	tmp = *content;
	total = 0;
	if (!check_size(content, co, li))
		return (0);
	tputs(tgetstr("ho", NULL), 0, &ft_inputchar);
	index = 0;
	while (tmp && (i = -1))
	{
		while (tmp && ++i < li && !(lencol = 0) && ++index)
		{
			if (ft_strlen(tmp->elem) > lencol)
				lencol = ft_strlen(tmp->elem);
			moove(total, i, tmp);
			tmp->index = index - 1;
			tmp = tmp->next;
		}
		total += (lencol + 4);
	}
	return (1);
}
