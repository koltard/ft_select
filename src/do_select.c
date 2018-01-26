/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:49:38 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/26 10:34:40 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_content	*st_2(t_content **content, t_content *tmp)
{
	t_content	*tmp2;

	tmp2 = *content;
	if (tmp == tmp2)
	{
		*content = tmp->next;
		tmp2 = tmp2->next;
		tmp->next = NULL;
		ft_strdel(&tmp->elem);
		free(tmp);
		return (*content);
	}
	while (tmp2->next != tmp)
		tmp2 = tmp2->next;
	ft_strdel(&tmp->elem);
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
			while (tmp2->next != tmp)
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
