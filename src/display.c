/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 11:40:53 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/23 17:02:30 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			count_max_len(char **tabl, int li)
{
	int		i;
	int		len;

	i = -1;
	len = 0;
	while (++i <= li && tabl[i])
		if (len < ft_strlen(tabl[i]))
			len = ft_strlen(tabl[i]);
	return (len);
}

static int	size_left(int co, int li, int ac, char **av)
{
	int		line_max;

	line_max = 0;
	while (ac > 0)
	{
		if (ac >= li)
		{
			line_max += (count_max_len(av, li) + 4);
			av += li;
			ac -= li;
		}
		else
		{
			line_max += (count_max_len(av, ac));
			av += ac;
			ac = 0;
		}
	}
	return (co - line_max);
}

static void	moove_print(int li, int len, char **av)
{
	int		i;
	int		len_col;
	int		len_tot;
	int		old_len;

	len_tot = 0;
	while (len > 0)
	{
		old_len = len_tot;
		len_col = count_max_len(av, li);
		len_tot += len_col + 4;
		i = 0;
		while (i < li && av[i])
		{
			ft_printf_fd(STDIN_FILENO, "%s", av[i]);
			i++;
			tputs(tgoto(tgetstr("cm", NULL), old_len, i), 0, ft_putchar);
		}
		tputs(tgoto(tgetstr("cm", NULL), len_tot, 0), 0, ft_putchar);
		len = len - li;
		av = av + i;
	}
}

void		display(int co, int li, int len, char **av)
{
	int		i;
	int		total;

	i = -1;
	total = size_left(co, li, len, av);
	tputs(tgetstr("me", NULL), 0, ft_putchar);
	tputs(tgetstr("cl", NULL), 0, ft_putchar);
	if (len < li)
		while (++i < len)
			ft_printf_fd(STDIN_FILENO, "%s\n", av[i]);
	else if (total >= 0)
		moove_print(li, len, av);
	else
		ft_putendl_fd("\033[31mScreen size too small\033[0m", STDERR_FILENO);
	tputs(tgetstr("ho", NULL), 0, ft_putchar);
}
