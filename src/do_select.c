/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:49:38 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/25 12:53:56 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	do_select(t_content *content)
{
	char	*tmp;

	tmp = content->current[content->index];
	if (!(content->select))
	{
		content->select = (char **)malloc(sizeof(char *) * 2);
		content->select[0] = ft_strdup(tmp);
		content->select[1] = NULL;
		put_color(content, 1);
	}
	else if (ft_tabchr(content->select, tmp))
	{
		content->select = delete_tab(content->select, tmp);
		put_color(content, 0);
	}
	else
	{
		content->select = put_new_tab(content->select, tmp);
		put_color(content, 1);
	}
}
