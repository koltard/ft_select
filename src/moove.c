/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 09:39:54 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/25 12:48:21 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			go_down(t_content **content, t_content *current)
{
	t_content	*tmp;

	tmp = *content;
	if (!current->next)
		;
	else
	{
		while (tmp->index != current->index + 1)
			tmp = tmp->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
	return (tmp->index);
}

int			go_up(t_content **content, t_content *current)
{
	t_content	*tmp;

	tmp = *content;
	if (!current->index)
	{
		while (tmp->next)
			tmp = tmp->next;
	}
	else
	{
		while (tmp->index != current->index - 1)
			tmp = tmp->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
	return (tmp->index);
}

int			go_right(t_content **content, t_content *current)
{
	t_content	*tmp;

	tmp = current;
	if (current->next)
	{
		tmp = tmp->next;
		while (tmp && tmp->y != current->y)
			tmp = tmp->next;
	}
	else
	{
		tmp = *content;
		while (tmp && tmp->y != current->y + 1)
			tmp = tmp->next;
	}
	if (!tmp)
	{
		tmp = *content;
		if (current->next && current->next->x == current->x)
			while (tmp->y != current->y + 1)
				tmp = tmp->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
	return (tmp->index);
}

static int	find_last_col(t_content **content, int y)
{
	int			check;
	t_content	*tmp;
	t_content	*tmp2;

	tmp = *content;
	check = 0;
	while (!check)
	{
		tmp2 = tmp->next;
		while (tmp2 && tmp2->y != y)
			tmp2 = tmp2->next;
		if (!tmp2)
			break ;
		tmp = tmp->next;
	}
	return (tmp->index);
}

int			go_left(t_content **content, t_content *current)
{
	t_content	*tmp;
	int			golast;

	tmp = *content;
	if (current->x != 0)
	{
		while (tmp->index + tgetnum("li") != current->index)
			tmp = tmp->next;
	}
	else
	{
		if (current->y != 0)
			golast = find_last_col(content, current->y - 1);
		else if (count_list(content) >= tgetnum("li"))
			golast = find_last_col(content, tgetnum("li") - 1);
		else
			golast = count_list(content) - 1;
		while (tmp->index != golast)
			tmp = tmp->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
	return (tmp->index);
}
