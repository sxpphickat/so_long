/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manage_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:43:57 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/06 11:05:57 by vipereir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_lines(char	*map_path)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(map_path, O_RDWR);
	if (fd == -1)
		map_error("File not found");
	line = get_next_line(fd);
	i++;
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
	if (i < 3)
		map_error("Map too small");
	return (i);
}

void	set_values(int *i, int *j, int *x, int *y)
{
	(*i) = 0;
	(*j)++;
	(*y) += 64;
	(*x) = 0;
}

void	initialize_line_row(int *i, int *j, int *x, int *y)
{
	(*i) = 0;
	(*j) = 0;
	(*y) = 0;
	(*x) = 0;
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	ft_zero(t_window *win)
{
	win->p_count = 0;
	win->c_count = 0;
	win->e_count = 0;
	win->error = 0;
	win->moves = 0;
}
