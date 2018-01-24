/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove_vert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 07:32:54 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/24 17:04:13 by kyazdani         ###   ########.fr       */
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

static int		get_ux(t_content *content)
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

static int	get_dx(t_content *content)
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
			content->x = get_dx(content);
		}
		else
			content->y++;
	}
	tputs(tgoto(tgetstr("cm", NULL), content->x, content->y), 0, &ft_inputchar);
}

void			go_up(t_content *content)
{
	if (content->y == 0)
	{
		if (content->x == 0)
		{
			content->index = content->len - 1;
			content->y = get_last(content) - 1;
			content->x = get_ux(content);
		}
		else
		{
			content->index--;
			content->y = tgetnum("li") - 1;
			content->x = get_ux(content);
		}
	}
	else
	{
		content->y--;
		content->index--;
	}
	tputs(tgoto(tgetstr("cm", NULL), content->x, content->y), 0, &ft_inputchar);
}
