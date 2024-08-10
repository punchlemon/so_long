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
# include <unistd.h>

// debug
#include <stdio.h>

typedef struct s_cordinate {
	size_t	x;
	size_t	y;
}	t_cordinate;

typedef struct s_map_info {
	int	p_cnt;
	int	c_cnt;
	int	e_cnt;
}	t_map_info;

typedef struct s_data {
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
}	t_data;

// tile.c
typedef struct s_tile {
	void	*mlx;
	void	*img;
	t_item	*file;
	int		width;
	int		height;
}	t_tile;
t_item	*create_tile(void *, char *, char *);
void	*delete_tile(void *);
int		print_tile(void *, int, int *);
void	enlarge_tiles(t_data *d, int mult);

// event_handler.c
int			key_event(int, t_data *);
int			close_mlx(t_data *);

#endif