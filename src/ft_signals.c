/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 13:07:06 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/26 14:50:39 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern int			g_check;
extern t_content	**g_out;

void	resize(int x)
{
	struct winsize	lico;

	(void)x;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &lico);
	if (!(g_check = display(lico.ws_col, lico.ws_row, g_out)))
		ft_putendl_fd("\033[31mSCREENSIZE TOO SMALL\033[0m", STDERR_FILENO);
	signal(SIGWINCH, (void (*)(int))resize);
}
