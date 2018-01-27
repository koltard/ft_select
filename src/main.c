/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:35:44 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/27 15:33:08 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_module		*g_module;

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

static void	init_module(t_content **content)
{
	g_module = malloc(sizeof(t_module));
	tcgetattr(STDIN_FILENO, &(g_module->cap_current));
	tcgetattr(STDIN_FILENO, &(g_module->cap_init));
	g_module->current = 0;
	g_module->checked = 0;
	g_module->ptr = content;
	ft_cfmakeraw(&(g_module->cap_current));
	tputs(tgetstr("vi", NULL), 0, &ft_inputchar);
}

static void	step_2(t_content *content)
{
	if (!(g_module->checked = display(&content)))
	{
		tputs(tgetstr("ho", NULL), 0, &ft_inputchar);
		ft_putendl_fd("\033[31mSCREENSIZE TOO SMALL\033[0m", STDIN_FILENO);
	}
	while (!g_module->checked)
		;
	tputs(tgetstr("ho", NULL), 0, &ft_inputchar);
	select_readtype(&content);
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	print_list(&content);
	if (content)
		free_list(&content);
}

int			main(int ac, char **av)
{
	t_content		*content;

	content = NULL;
	if (ac == 1 && ft_printf_fd(2, "error: ft_select: Arguments required\n"))
		return (0);
	if (!init_termcaps())
		return (0);
	mount_list(&content, &av[1]);
	init_module(&content);
	signal(SIGTSTP, (void (*)(int))q_process);
	signal(SIGINT, (void (*)(int))quit_proper);
	signal(SIGCONT, (void(*)(int))c_process);
	signal(SIGWINCH, (void (*)(int))resize);
	step_2(content);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_module->cap_init);
	free(g_module);
	tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
	return (0);
}
