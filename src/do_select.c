/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:49:38 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/28 19:32:16 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_module	*g_module;

static t_content	*st_2(t_content **content, t_content *tmp)
{
	t_content	*tmp2;

	ft_strdel(&tmp->elem);
	if (tmp == *content)
	{
		*content = tmp->next;
		tmp->next = NULL;
		free(tmp);
		g_module->ptr = content;
		return (*content);
	}
	tmp2 = *content;
	while (tmp2->next != tmp)
		tmp2 = tmp2->next;
	tmp2->next = tmp->next;
	tmp->next = NULL;
	free(tmp);
	return (tmp2);
}

t_content			*delete_elm(t_content **content, t_content *tmp)
{
	t_content	*tmp2;

	if (!tmp->next)
	{
		ft_strdel(&tmp->elem);
		if (tmp == *content)
		{
			free(*content);
			*content = NULL;
			return (NULL);
		}
		else
		{
			tmp2 = *content;
			while (tmp2 && tmp2->next != tmp)
				tmp2 = tmp2->next;
			free(tmp);
			tmp2->next = NULL;
			return (tmp2);
		}
	}
	else
		return (st_2(content, tmp));
}

t_content			*do_select(t_content **content, t_content *tmp)
{
	if (!tmp->check)
	{
		tmp->check = 1;
		print_under(0, tmp);
		print_color(tmp);
		tmp = go_down(content, tmp);
		tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
		print_under(1, tmp);
		return (tmp);
	}
	else
	{
		tmp->check = 0;
		print_color(tmp);
		print_under(1, tmp);
		return (tmp);
	}
}
