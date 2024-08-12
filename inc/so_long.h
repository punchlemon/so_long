/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:41:15 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 15:41:16 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ESC 65307
# define LEFT 65361
# define UP 65362
# define RIGHT 65363
# define DOWN 65364
# define LEFT_A 97
# define UP_W 119
# define DOWN_S 115
# define RIGHT_D 100

# define C 2
# define E 3
# define P 4

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>

typedef struct s_cordinate
{
	size_t	y;
	size_t	x;
}	t_cordinate;

typedef struct s_map_info
{
	int	p_cnt;
	int	c_cnt;
	int	e_cnt;
}	t_map_info;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		*addr;
	t_item		**tiles;
	int			width;
	int			height;
	t_item		*ber;
	int			**map;
	t_cordinate	map_size;
	t_map_info	map_inf;
	int			player_move;
	int			get_coin;
}	t_data;

// tile.c
typedef struct s_tile
{
	void	*mlx;
	void	*img;
	t_item	*file;
	int		width;
	int		height;
}	t_tile;
t_item	*create_tile(void *mlx, char *path, char *name);
void	*delete_tile(void *tile);
int		print_tile(void *tile, int fd, int *res);
void	enlarge_tiles(t_data *d, int mult);

// event_handler.c
void	ft_putnbr_fd(int n, int fd);
void	success(t_data *d);
int		error(t_data *d, char *str);
int		close_mlx(t_data *d);
int		key_event(int key, t_data *d);

// flood_fill.c
int		flood_fill_rec(t_cordinate map_size, int **map, size_t y, size_t x);
void	get_cordinate(t_data *d, t_cordinate *cord, int i);
void	flood_fill(t_data *d);

// map.c
void	disp_map(t_data *d);
int		get_num(char c);
void	set_map(t_data *d, t_list *start);
void	update_map(t_data *d, int key);

// map_check.c
void	width_chk(t_data *d, t_list *start, t_cordinate *map_size);
void	surround_one_chk(t_data *d, t_list *start, t_cordinate *map_size);
void	include_char_chk(t_data *d, t_list *l);
int		check_file(t_data *d);

// handling_arguments.c
int		handling_arguments(t_data *d, int argc, char **argv);

#endif
