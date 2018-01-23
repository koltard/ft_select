/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 10:59:01 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/23 13:41:17 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	get_x(t_content *content)
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
			content->x += get_x(content);
		content->index += tgetnum("li");
	}
	tputs(tgoto(tgetstr("cm", NULL), content->x, content->y), 0, ft_putchar);
}
