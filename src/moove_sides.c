/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_sides.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 09:39:54 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/24 08:08:51 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	get_last_col(t_content *content)
{
	int		i;
	int		total;
	char	**tmp;

	i = 0;
	total = 0;
	tmp = content->current;
	if (content->y == 0)
		content->y = tgetnum("li") - 1;
	else
		content->y--;
	while (i + tgetnum("li") + content->y < content->len)
	{
		total += count_max_len(&tmp[i], tgetnum("li")) + 4;
		if (i + tgetnum("li") + content->y < content->len)
			i += tgetnum("li");
	}
	content->index = i + content->y;
	return (total);
}

static int	get_lx(t_content *content)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = content->current;
	while (i + tgetnum("li") + content->y < content->index)
		i += tgetnum("li");
	return (count_max_len(&tmp[i], tgetnum("li")) + 4);
}

static int	get_rx(t_content *content)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = content->current;
	while (i <= content->index)
		i += tgetnum("li");
	i -= tgetnum("li");
	return (count_max_len(&tmp[i], tgetnum("li")) + 4);
}

void		go_right(t_content *content)
{
	if (content->index + tgetnum("li") > content->len - 1)
	{
		content->x = 0;
		if (content->y == tgetnum("li") - 1)
			content->y = 0;
		else
			content->y++;
		content->index = content->y;
	}
	else
	{
		if (content->x == 0)
			content->x = count_max_len(content->current, tgetnum("li")) + 4;
		else
			content->x += get_rx(content);
		content->index += tgetnum("li");
	}
	tputs(tgoto(tgetstr("cm", NULL), content->x, content->y), 0, ft_putchar);
}

void		go_left(t_content *content)
{
	if (content->x == 0)
		content->x = get_last_col(content);
	else
	{
		content->x -= get_lx(content);
		content->index -= tgetnum("li");
	}
	tputs(tgoto(tgetstr("cm", NULL), content->x, content->y), 0, ft_putchar);
}
