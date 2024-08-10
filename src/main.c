#include "so_long.h"
#include <stdio.h>

void	disp_map(t_data *d)
{
	int		x;
	int		y;
	int		i;
	t_tile	*t;

	x = -1;
	while (++x < 5)
	{
		y = -1;
		while (++y < 5)
		{
			i = d->map[y][x];
			t = ((t_tile *)d->tiles[i]->addr);
			mlx_put_image_to_window(d->mlx, d->win, t->img, x * t->width, y * t->height);
		}
	}
}

int	set_img(t_data *d)
{
	d->tiles = malloc(sizeof(t_tile *) * 5);
	if (!d->tiles)
		return (close_mlx(d));
	d->tiles[0] = create_tile(d->mlx, "img/sky.xpm", "sky");
	d->tiles[1] = create_tile(d->mlx, "img/renga.xpm", "renga");
	d->tiles[2] = create_tile(d->mlx, "img/coin.xpm", "coin");
	d->tiles[3] = create_tile(d->mlx, "img/flag.xpm", "flag");
	d->tiles[4] = create_tile(d->mlx, "img/mario.xpm", "mario");
	d->map = malloc(sizeof(int *) * 5);
	if (!d->map)
		return (close_mlx(d));
	enlarge_tiles(d, 5);
	return (0);
}

int	width_check(t_list *l, int line_num)
{
	t_list		*l;
	int		i;
	int		width;

	width = ((t_string *)(l->item->addr))->len;
	if (width < 3)
		return (1);
	i = 0;
	while (++i < line_num)
	{
		l = l->next;
		if (width != ((t_string *)(l->item->addr))->len)
			return (1); 
	}
	return (0);
}

int	all_one_check(t_list *l, int line_num)
{
}

int	include_char_check(t_list *l, int line_num)
{
}

int	check_file(t_item *file)
{
	t_file		*f;
	t_list		*l;
	int			line_num;
	t_string	*s;

	if (!file)
		return (1);
	f = (t_file *)(file->addr);
	if (!f->lines)
		return (1);
	line_num = f->line_num;
	if (line_num < 3)
		return (1);
	l = ((t_list *)(f->lines->addr))->next;
	if (width_check(l, line_num))
		return (1);
	if (all_one_check(l, line_num))
		return (1);
	if (include_char_check(l, line_num))
		return (1);
	return (0);
}

int main(void)
{
	t_data	d;

	d.mlx = mlx_init();
	d.width = 960;
	d.height = 540;
	d.win = mlx_new_window(d.mlx, d.width, d.height, "So_long");
	set_img(&d);
	d.ber = create_file("test.ber", "test");
	if (check_file(d.ber))
		return (close_mlx(&d), write(1, "file error\n", 11), 0);
	d.map[0] = malloc(sizeof(int) * 5);
	d.map[1] = malloc(sizeof(int) * 5);
	d.map[2] = malloc(sizeof(int) * 5);
	d.map[3] = malloc(sizeof(int) * 5);
	d.map[4] = malloc(sizeof(int) * 5);
	if (!d.map[0] || !d.map[1] || !d.map[2] || !d.map[3] || !d.map[4])
		return (close_mlx(&d));
	int	map[5][5] = {
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 2, 0, 1},
		{1, 4, 0, 3, 1},
		{1, 1, 1, 1, 1}
	};
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			d.map[i][j] = map[i][j];
		}
	}
	disp_map(&d);

	// d.addr = mlx_get_data_addr(d.tile->img, &d.bpp, &d.line_length, &d.endian);
	// res = 0;
	// f = create_file("src/main.c", "main");
	// print(f, 1, &res);
	// delete(f);

	mlx_hook(d.win, 17, 0, close_mlx, &d);
	mlx_key_hook(d.win, key_event, &d);
	mlx_loop(d.mlx);
	return (0);
}
