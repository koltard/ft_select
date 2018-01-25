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

int 	do_select(t_content **content, int index)
{
	t_content	*tmp;
    int         ret;

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
