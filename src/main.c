/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:35:44 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/24 18:15:02 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		print_tab(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		ft_printf_fd(STDOUT_FILENO, "%s ", str[i]);
	if (str[0])
		write(STDOUT_FILENO, "\n", 1);
	return (1);
}

void	init_content(t_content *content, int ac)
{
	content->x = 0;
	content->y = 0;
	content->len = ac;
	content->index = 0;
	content->current = NULL;
	content->select = NULL;
}

int		main(int ac, char **av)
{
	struct termios	my_state;
	t_content		content;

	if (ac == 1 && ft_printf_fd(2, "error: ft_select: Arguments required\n"))
		return (0);
	if (!init_termcaps())
		return (0);
	tcgetattr(STDIN_FILENO, &my_state);
	ft_cfmakeraw(&my_state);
	init_content(&content, ac - 1);
	content.current = cpy_av(&av[1], ac - 1);
	display(tgetnum("co"), tgetnum("li"), &content);
	tputs(tgetstr("vi", NULL), 0, &ft_inputchar);
	underline(1, &content);
	select_readtype(&content);
	tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	if (content.select && print_tab(content.select))
		ft_freetab(content.select);
	ft_freetab(content.current);
	ft_cfmakedefault(&my_state);
	return (0);
}
