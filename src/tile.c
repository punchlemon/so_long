#include "so_long.h"

void	delete_tile(void *mlx, t_tile *t)
{
	if (!t)
		return ;
	if (t->img)
		mlx_destroy_image(mlx, t->img);
	delete_string(t->path);
	delete_string(t->name);
	free(t);
}

t_tile	*create_tile(void *mlx, char *path, char *name)
{
	t_tile	*t;

	t = malloc(sizeof(t_tile));
	if (!t)
		return (NULL);
	t->path = create_string(path);
	t->name = create_string(name);
	t->img = mlx_xpm_file_to_image(mlx, t->path->str, &t->width, &t->height);
	if (!t->img)
		return (delete_tile(mlx, t), NULL);
	return (t);
}
