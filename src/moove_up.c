/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 07:32:54 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/23 09:28:02 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		get_last(t_content *content)
{
	int		len;
	int		li;

	len = content->len;
	li = tgetnum("li");
	while (len > li)
		len = len - li;
	return (len);
}

static int		get_x(t_content *content)
{
	char	**tmp;
	int		len;
	int		i;

	tmp = content->current;
	len = 0;
	i = 0;
	while (content->x == 0 && i + tgetnum("li") < content->len)
	{
		len += count_max_len(&tmp[i], tgetnum("li")) + 4;
		i += tgetnum("li");
	}
	while (content->x != 0
			&& len + count_max_len(&tmp[i], tgetnum("li")) + 4 < content->x)
	{
		len += count_max_len(&tmp[i], tgetnum("li")) + 4;
		i += tgetnum("li");
	}
	return (len);
}

void			go_up(t_content *content)
{
	if (content->y == 0)
	{
		if (content->x == 0)
		{
			content->index = content->len - 1;
			content->y = get_last(content) - 1;
			content->x = get_x(content);
		}
		else
		{
			content->index--;
			content->y = tgetnum("li") - 1;
			content->x = get_x(content);
		}
	}
	else
	{
		content->y--;
		content->index--;
	}
	tputs(tgoto(tgetstr("cm", NULL), content->x, content->y), 0, ft_putchar);
}
