/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_left.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 09:39:54 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/23 16:42:43 by kyazdani         ###   ########.fr       */
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

static int	get_x(t_content *content)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = content->current;
	while (i + tgetnum("li") + content->y < content->index)
		i += tgetnum("li");
	return (count_max_len(&tmp[i], tgetnum("li")) + 4);
}

void		go_left(t_content *content)
{
	if (content->x == 0)
		content->x = get_last_col(content);
	else
	{
		content->x -= get_x(content);
		content->index -= tgetnum("li");
	}
	tputs(tgoto(tgetstr("cm", NULL), content->x, content->y), 0, ft_putchar);
}
