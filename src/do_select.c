/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:49:38 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/26 08:18:37 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	st_2(t_content **content, t_content *tmp)
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
		return (0);
	}
	while (tmp2->next != tmp)
		tmp2 = tmp2->next;
	ft_strdel(&tmp->elem);
	tmp2->next = tmp->next;
	free(tmp);
	tmp->next = NULL;
	return (tmp2->index);
}

int			delete_elm(t_content **content, int index)
{
	t_content	*tmp;
	t_content	*tmp2;

	tmp = find_elm(content, index);
	if (!tmp->next)
	{
		ft_strdel(&tmp->elem);
		if (tmp == *content)
		{
			free(*content);
			*content = NULL;
			return (-1);
		}
		else
		{
			tmp2 = *content;
			while (tmp2->next != tmp)
				tmp2 = tmp2->next;
			free(tmp);
			tmp2->next = NULL;
			return (tmp2->index);
		}
	}
	else
		return (st_2(content, tmp));
}

int			do_select(t_content **content, int index)
{
	t_content	*tmp;
	int			ret;

	tmp = *content;
	ret = 0;
	while (tmp->index != index)
		tmp = tmp->next;
	if (!tmp->check)
	{
		tmp->check = 1;
		print_under(0, tmp->index, content);
		print_color(index, content);
		ret = go_down(content, tmp);
		print_under(1, ret, content);
		return (ret);
	}
	else
	{
		tmp->check = 0;
		print_color(index, content);
		print_under(1, index, content);
		return (index);
	}
}
