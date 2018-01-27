/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:07:06 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/27 17:45:06 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_module		*g_module;

void	c_process(int x)
{
	t_content	*tmp;

	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_module->cap_current);
	tputs(tgetstr("vi", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	if (!(g_module->checked = display(g_module->ptr)))
		ft_putendl_fd("\033[31mSCREENSIZE TOO SMALL\033[0m", STDERR_FILENO);
	else
	{
		tmp = *(g_module->ptr);
		while (tmp->index != g_module->current)
			tmp = tmp->next;
		tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
		print_under(1, tmp);
	}
	signal(SIGCONT, (void (*)(int))c_process);
	signal(SIGTSTP, (void (*)(int))q_process);
	(void)x;
}

void	q_process(int x)
{
	char			tmp[2];

	tmp[0] = '\032';
	tmp[1] = '\0';
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_module->cap_init);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN_FILENO, TIOCSTI, tmp);
	(void)x;
}

void	quit_proper(int x)
{
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
	free_list(g_module->ptr);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_module->cap_init);
	free(g_module);
	exit(1);
	(void)x;
}

void	resize(int x)
{
	t_content	*tmp;

	if (!(g_module->checked = display(g_module->ptr)))
		ft_putendl_fd("\033[31mSCREENSIZE TOO SMALL\033[0m", STDERR_FILENO);
	else
	{
		tmp = *(g_module->ptr);
		while (tmp->index != g_module->current)
			tmp = tmp->next;
		tputs(tgoto(tgetstr("cm", NULL), tmp->x, tmp->y), 0, &ft_inputchar);
		print_under(1, tmp);
	}
	signal(SIGWINCH, (void (*)(int))resize);
	(void)x;
}
