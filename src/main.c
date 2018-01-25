/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:35:44 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/25 12:37:18 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		main(int ac, char **av)
{
	struct termios	my_state;
	t_content		*content;
	int				ret;

	content = NULL;
	if (ac == 1 && ft_printf_fd(2, "error: ft_select: Arguments required\n"))
		return (0);
	if (!init_termcaps())
		return (0);
	tcgetattr(STDIN_FILENO, &my_state);
	ft_cfmakeraw(&my_state);
	mount_list(&content, &av[1]);
	ret = display(tgetnum("co"), tgetnum("li"), &content);
	tputs(tgetstr("vi", NULL), 0, &ft_inputchar);
	tputs(tgetstr("ho", NULL), 0, &ft_inputchar);
	print_under(1, 0, &content);
	select_readtype(&content);
	tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
// print list here
	ft_cfmakedefault(&my_state);
	return (0);
}
