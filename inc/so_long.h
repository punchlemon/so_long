#ifndef SO_LONG_H
# define SO_LONG_H

# define ESC 65307

# include "libft.h"
# include <mlx.h>
# include <stdlib.h>

typedef struct s_data {
	void	*mlx;
	void	*win;
	char	*addr;
	t_item	**tiles;
	int		width;
	int		height;
	t_item	*ber;
	int		**map;
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