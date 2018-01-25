/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mount_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 06:59:25 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/25 12:49:28 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int					count_list(t_content **list)
{
	int			i;
	t_content	*tmp;

	i = 0;
	tmp = *list;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

static void			push_back(t_content **list, t_content *new)
{
	t_content	*tmp;

	if (!*list)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static t_content	*new_content(char *str, int i)
{
	t_content	*new;

	new = (t_content *)malloc(sizeof(t_content));
	new->elem = ft_strdup(str);
	new->index = i;
	new->x = 0;
	new->y = 0;
	new->check = 0;
	new->next = NULL;
	return (new);
}

void				mount_list(t_content **content, char **av)
{
	int			i;
	t_content	*new;

	i = -1;
	while (av[++i])
	{
		new = NULL;
		new = new_content(av[i], i);
		push_back(content, new);
	}
}
