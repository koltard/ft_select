/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:35:44 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/26 14:39:52 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern int			g_check;
extern t_content	**g_out;

static void	print_list(t_content **list)
{
	t_content	*tmp;
	int			check;

	tmp = *list;
	check = 0;
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	while (tmp)
	{
		if (tmp->check)
		{
			ft_putstr(tmp->elem);
			write(1, " ", 1);
			check = 1;
		}
		tmp = tmp->next;
	}
	if (check)
		write(1, "\n", 1);
}

static void	step_2(t_content *content)
{
	tputs(tgetstr("vi", NULL), 0, &ft_inputchar);
	g_out = &content;
	g_check = 0;
	signal(SIGWINCH, (void (*)(int))resize);
	if (!(g_check = display(tgetnum("co"), tgetnum("li"), &content)))
	{
		tputs(tgetstr("ho", NULL), 0, &ft_inputchar);
		ft_putendl_fd("\033[31mSCREENSIZE TOO SMALL\033[0m", STDIN_FILENO);
	}
	while (!g_check)
		;
	tputs(tgetstr("ho", NULL), 0, &ft_inputchar);
	print_under(1, content);
	select_readtype(&content);
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	print_list(&content);
	if (content)
		free_list(&content);
	tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
}

int			main(int ac, char **av)
{
	struct termios	my_state;
	t_content		*content;

	content = NULL;
	if (ac == 1 && ft_printf_fd(2, "error: ft_select: Arguments required\n"))
		return (0);
	if (!init_termcaps())
		return (0);
	tcgetattr(STDIN_FILENO, &my_state);
	ft_cfmakeraw(&my_state);
	mount_list(&content, &av[1]);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	step_2(content);
	ft_cfmakedefault(&my_state);
	return (0);
}
