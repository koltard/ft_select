/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:07:06 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/27 12:12:08 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern int			g_check;
extern t_content	**g_out;

void	c_process(int x)
{
	struct winsize	lico;
	struct termios	state;

	(void)x;
	tcgetattr(STDIN_FILENO, &state);
	ft_cfmakeraw(&state);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &lico);
	tputs(tgetstr("vi", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	if (!(g_check = display(lico.ws_col, lico.ws_row, g_out)))
		ft_putendl_fd("\033[31mSCREENSIZE TOO SMALL\033[0m", STDERR_FILENO);
	signal(SIGCONT, (void (*)(int))c_process);
	signal(SIGTSTP, (void (*)(int))q_process);
}

void	q_process(int x)
{
	struct termios	state;

	(void)x;
	tputs(tgetstr("me", NULL), 0, &ft_inputchar);
	tputs(tgetstr("cl", NULL), 0, &ft_inputchar);
	tputs(tgetstr("ve", NULL), 0, &ft_inputchar);
	tcgetattr(STDIN_FILENO, &state);
	ft_cfmakedefault(&state);
	signal(SIGTSTP, SIG_DFL);
}

void	resize(int x)
{
	struct winsize	lico;

	(void)x;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &lico);
	if (!(g_check = display(lico.ws_col, lico.ws_row, g_out)))
		ft_putendl_fd("\033[31mSCREENSIZE TOO SMALL\033[0m", STDERR_FILENO);
	signal(SIGWINCH, (void (*)(int))resize);
}
