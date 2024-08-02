#ifndef SO_LONG_H
# define SO_LONG_H

# define ESC 65307

# include "ft_lib.h"
# include <mlx.h>
# include <stdlib.h>

typedef struct s_tile {
	void		*img;
	t_string	*path;
	t_string	*name;
	int			width;
	int			height;
}	t_tile;

typedef struct s_data {
	void	*mlx;
	void	*win;
	char	*addr;
	t_tile	*tile;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;

// event_handler.c
int			key_event(int, t_data *);
int			close_mlx(t_data *);

// get_next_line.c
char		*get_next_line(int);

// tile.c
t_tile		*create_tile(void *, char *, char *);
void		delete_tile(void *, t_tile *);

#endif