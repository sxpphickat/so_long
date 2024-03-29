/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:39:22 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/06 11:36:57 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	valid_map(t_window *win)
{
	border_valid(win);
	info_count(win);
	map_size_verify(win);
	if (win->error == -3)
		map_error_free("Map borders shold be 1", win);
	else if (win->error == -1)
		map_error_free("Map can only contain C, P, E, 0 and 1", win);
	else if (win->p_count != 1 || win->c_count == 0 || win->e_count != 1)
		map_error_free("Map should have 1 'P', 1 'E' and at least 1 'C'", win);
	else if (win->error == -4)
		map_error_free("Your map can't be a square!", win);
	else if (win->error == -2)
		map_error_free("Map isn's a rectangle", win);
	else if (is_playable(win) == 1)
		map_error_free("Map path isn't playable", win);
	return (0);
}

int	is_playable(t_window *win)
{
	char	**temp;

	player_possition(win);
	temp = map_copy(win->map);
	iterate_map(temp, win->p_x, win->p_y);
	if (check_exit(win, temp) == 1 || collect_count(temp) == 1)
	{
		ft_free_matrix(temp);
		return (1);
	}
	ft_free_matrix(temp);
	return (0);
}

int	check_exit(t_window *win, char **map)
{
	exit_possition(win);
	if (map[win->e_y][win->e_x + 1] == 'X'
			|| map[win->e_y][win->e_x - 1] == 'X'
			|| map[win->e_y + 1][win->e_x] == 'X'
			|| map[win->e_y - 1][win->e_x] == 'X')
		return (0);
	return (1);
}

void	iterate_map(char **map, int i, int j)
{
	if (map[j][i + 1] == '0' || map[j][i + 1] == 'C')
	{
		map[j][i + 1] = 'X';
		iterate_map(map, i + 1, j);
	}
	if (map[j][i - 1] == '0' || map[j][i - 1] == 'C')
	{
		map[j][i - 1] = 'X';
		iterate_map(map, i - 1, j);
	}
	if (map[j - 1][i] == '0' || map[j - 1][i] == 'C')
	{
		map[j - 1][i] = 'X';
		iterate_map(map, i, j - 1);
	}
	if (map[j + 1][i] == '0' || map[j + 1][i] == 'C')
	{
		map[j + 1][i] = 'X';
		iterate_map(map, i, j + 1);
	}
}

void	border_valid(t_window *win)
{
	int	i;
	int	j;

	i = 0;
	j = line_count(win->map) - 1;
	win->line_length = ft_strlen(win->map[0]);
	while (win->map[0][i] != '\n')
	{
		if (win->map[0][i] != '1' || win->map[j][i] != '1')
			return (ft_error(win));
		i++;
	}
	j = 0;
	while (win->map[j] != NULL)
	{
		if (win->map[j][0] != '1' ||
			win->map[j][win->line_length - 2] != '1')
			return (ft_error(win));
		j++;
	}
}
