/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:06:20 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/04 17:06:38 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_win(void)
{
	ft_printf("\033[22;95mYou Win!\n\033[0m");
	exit(0);
}

int	close_x(void)
{
	exit(0);
}

void	ft_error(t_window *win)
{
	win->error = 1;
	return ;
}

void	map_error(void)
{
	ft_putstr_fd("\033[22;31mError\n\033[0m", 2);
	ft_putstr_fd("\033[22;31mMap error\n\033[0m", 2);
	exit(0);
}