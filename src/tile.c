#include "so_long.h"

void	*delete_tile(void *tile)
{
	t_tile	*t;

	if (!tile)
		return (NULL);
	t = (t_tile *)tile;
	if (t->img)
		mlx_destroy_image(t->mlx, t->img);
	if (t->file)
		delete(t->file);
	free(t);
	return (NULL);
}

t_item	*create_tile(void *mlx, char *path, char *name)
{
	t_item	*res;
	t_tile	*t;

	res = malloc(sizeof(t_item));
	if (!res)
		return (NULL);
	t = malloc(sizeof(t_tile));
	if (!t)
		return (free(res), NULL);
	res->addr = t;
	res->delete = delete_tile;
	res->print = print_tile;
	t->file = create_file(path, name);
	if (!t->file)
		return (delete(res), NULL);
	t->mlx = mlx;
	t->img = mlx_xpm_file_to_image(mlx, path, &t->width, &t->height);
	if (!t->img)
		return (delete(res), NULL);
	return (res);
}

int	print_tile(void *tile, int fd, int *res)
{
	t_tile	*t;
	int		tmp;

	t = (t_tile *)tile;
	tmp = print(t->file, fd, res);
	if (tmp == -1)
		return (*res = -1, -1);
	*res += tmp;
	return (*res);
}

void	fill(int *new_data, int new_width, int pixel, int mult)
{
	int	y;
	int	x;

	y = -1;
	while (++y < mult)
	{
		x = -1;
		while (++x < mult)
			new_data[y * new_width + x] = pixel;
	}
}

void	enlarge_img(t_tile *t, void *new_img, int m)
{
	int	t_w;
	int	x;
	int	y;
	int	*new;
	int	*old;

	t_w = t->width;
	new = (int *)mlx_get_data_addr(new_img, &x, &x, &x);
	old = (int *)mlx_get_data_addr(t->img, &x, &x, &x);
	y = -1;
	while (++y < t->height)
	{
		x = -1;
		while (++x < t_w)
			fill(new + (y * t_w * m + x) * m, t_w * m, old[y * t_w + x], m);
	}
}

void	enlarge_tiles(t_data *d, int mult)
{
	void	*new_img;
	t_tile	*t;
	int		i;

	i = -1;
	while (++i < 5)
	{
		t = (t_tile *)(d->tiles[i]->addr);
		new_img = mlx_new_image(d->mlx, t->width * mult, t->height * mult);
		enlarge_img(t, new_img, mult);
		t->width *= mult;
		t->height *= mult;
		mlx_destroy_image(d->mlx, t->img);
		t->img = new_img;
	}
}
