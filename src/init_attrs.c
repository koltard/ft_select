/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_attrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyazdani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:09:06 by kyazdani          #+#    #+#             */
/*   Updated: 2018/01/22 15:20:43 by kyazdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_cfmakeraw(struct termios *my_state)
{
	my_state->c_lflag &= ~(ICANON | ECHO | ISIG);
	my_state->c_cc[VMIN] = 1;
	my_state->c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, my_state);
}

void	ft_cfmakedefault(struct termios *my_state)
{
	my_state->c_lflag |= (ICANON | ECHO | ISIG);
	tcsetattr(STDIN_FILENO, TCSADRAIN, my_state);
}
