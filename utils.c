/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipereir <vipereir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:09:41 by vipereir          #+#    #+#             */
/*   Updated: 2022/10/01 15:13:25 by sphh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_name(char	*map)
{
	int	len;

	len = ft_strlen(map);
	while(len > 4)
	{
		map++;
		len--;
	}
	return (ft_strncmp(map, ".ber", len));
}

char	**map_create(char	*map_path)
{
	char	**map;
	char	*line1;
	int		fd;
	int		i;

	i = 0;
	fd = open(map_path, O_RDWR);
	if (fd == -1)
		map_error(); //tratar esse error;
	line1 = get_next_line(fd);
	map = ft_calloc(sizeof(char *), ft_strlen(line1) + 1);
	map[i++] = line1;
	while (1)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
			break ;
		i++;
	}
	close(fd);
	return (map);
}

void	put_sprite(t_window *win, char *path, int x, int y)
{
	void	*img;
	int		img_width;
	int		img_height;

	img = mlx_xpm_file_to_image(win->mlx, path, &img_width, &img_height);
	mlx_put_image_to_window(win->mlx, win->win, img, x, y);
	mlx_destroy_image(win->mlx, img);
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

void	print_map(t_window *win)
{
	int	i;
	int	j;
	int	x;
	int	y;

	initialize_line_row(&i, &j, &x, &y);
	while (win->map[j] != NULL)
	{
		if (win->map[j][i] == '1')
			put_sprite(win, "./assets/wall64.xpm", x, y);
		else if (win->map[j][i] == '0')
			put_sprite(win, "./assets/ground64.xpm", x, y);
		else if (win->map[j][i] == 'P')
			put_sprite(win, "./assets/player64.xpm", x, y);
		else if (win->map[j][i] == 'C')
			put_sprite(win, "./assets/colect64.xpm", x, y);
		else if (win->map[j][i] == 'E' && win->c_count > 0)
			put_sprite(win, "./assets/exit64.xpm", x, y);
		else if (win->map[j][i] == 'E' && win->c_count == 0)
			put_sprite(win, "./assets/exit64.xpm", x, y);
		x += 64;
		i++;
		if (win->map[j][i] == '\n')

			set_values(&i, &j, &x, &y);
	}
}

void	create_win(t_window *win)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (win->map[0][x] != '\n')
		x++;
	while (win->map[y] != NULL)
		y++;
	win->win = mlx_new_window(win->mlx, (x * 64), (y * 64), "so_long");
}

void	player_possition(t_window *win)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (win->map[j] != NULL)
	{
		if (win->map[j][i] == 'P')
		{
			win->p_x = i;
			win->p_y = j;
		}
		i++;
		if (win->map[j][i] == '\n')
		{
			j++;
			i = 0;
		}
	}
}

void	ft_win(void)
{
	ft_printf("\033[22;95mYou Win!\n\033[0m");
	exit(0);
}

void	move_player(t_window *win, int x, int y)
{
	if (win->map[win->p_y + y][win->p_x + x] == '1')
		return ;
	if (win->map[win->p_y + y][win->p_x + x] == 'E' && win->c_count == 0)
		ft_win();
	else if (win->map[win->p_y + y][win->p_x + x] == 'E' && win->c_count > 0)
		return ;
	if (win->map[win->p_y + y][win->p_x + x] == 'C')
		win->c_count--;
	win->map[win->p_y][win->p_x] = '0';
	win->map[win->p_y + y][win->p_x + x] = 'P';
	win->moves++;
	ft_printf("%i\n", win->moves);
}

int	close_x(void)
{
	exit(0);
}
