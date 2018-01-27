/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:07:06 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/27 13:59:59 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern int			g_check;
extern t_content	**g_out;

void	c_process(int x)
{
	struct termios	state;

	(void)x;
	tcgetattr(STDIN_FILENO, &state);
	ft_cfmakeraw(&state);
	tputs(tgetstr("vi", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	if (!(g_check = display(g_out)))
		ft_putendl_fd("\033[31mSCREENSIZE TOO SMALL\033[0m", STDERR_FILENO);
	signal(SIGCONT, (void (*)(int))c_process);
	signal(SIGTSTP, (void (*)(int))q_process);
}

void	q_process(int x)
{
	struct termios	state;
	char			tmp[2];

	(void)x;
	tmp[0] = '\032';
	tmp[1] = '\0';
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
	tcgetattr(STDIN_FILENO, &state);
	ft_cfmakedefault(&state);
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN_FILENO, TIOCSTI, tmp);
}

void	quit_proper(int x)
{
	struct termios	state;

	(void)x;
	free_list(g_out);
	tcgetattr(STDIN_FILENO, &state);
	ft_cfmakedefault(&state);
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
	signal(SIGINT, SIG_DFL);
}

void	resize(int x)
{
	(void)x;
	if (!(g_check = display(g_out)))
		ft_putendl_fd("\033[31mSCREENSIZE TOO SMALL\033[0m", STDERR_FILENO);
	signal(SIGWINCH, (void (*)(int))resize);
}
