/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_down.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 09:21:15 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/23 13:40:55 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	get_x(t_content *content)
{
	int		len;
	int		i;
	char	**tmp;

	len = 0;
	i = 0;
	tmp = content->current;
	while (len <= content->x)
	{
		len += count_max_len(&tmp[i], tgetnum("li")) + 4;
		i += tgetnum("li");
	}
	return (len);
}

void		go_down(t_content *content)
{
	if (content->index == content->len - 1)
	{
		content->index = 0;
		content->x = 0;
		content->y = 0;
	}
	else
	{
		content->index++;
		if (content->y + 1 > tgetnum("li") - 1)
		{
			content->y = 0;
			content->x = get_x(content);
		}
		else
			content->y++;
	}
	tputs(tgoto(tgetstr("cm", NULL), content->x, content->y), 0, ft_putchar);
}
