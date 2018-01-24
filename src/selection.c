/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 16:06:23 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/24 18:29:24 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		ft_tabchr(char **tabl, char *str)
{
	int		i;

	i = -1;
	if (!tabl)
		return (0);
	while (tabl[++i])
		if (ft_strequ(tabl[i], str))
			return (1);
	return (0);
}

char	**delete_tab(char **tabl, char *str)
{
	char	**new;
	int		i;
	int		j;

	if (!(new = (char **)malloc(sizeof(char *) * (ft_tablen(tabl)))))
		return (NULL);
	i = -1;
	j = 0;
	while (tabl[++i])
	{
		if (ft_strequ(tabl[i], str) && j == i)
			free(tabl[i]);
		else
		{
			new[j] = tabl[i];
			j++;
		}
	}
	new[j] = NULL;
	ft_memdel((void **)&tabl);
	return (new);
}

char	**put_new_tab(char **tabl, char *str)
{
	char	**new;
	int		len;
	int		i;

	i = -1;
	len = ft_tablen(tabl);
	if (!(new = (char **)malloc(sizeof(char *) * (len + 2))))
		return (NULL);
	while (tabl[++i])
		new[i] = tabl[i];
	new[i] = ft_strdup(str);
	new[i + 1] = NULL;
	ft_memdel((void **)&tabl);
	return (new);
}

char	**cpy_av(char **str, int len)
{
	char	**new;
	int		i;

	i = -1;
	if (!(new = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	while (str[++i])
		new[i] = ft_strdup(str[i]);
	new[i] = NULL;
	return (new);
}
