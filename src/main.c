#include "so_long.h"
#include <stdio.h>

void	disp_map(t_data *d)
{
	t_cordinate	cord;
	int			i;
	t_tile		*t;

	cord.y = -1;
	while (++cord.y < d->map_size.y)
	{
		cord.x = -1;
		while (++cord.x < d->map_size.x)
		{
			i = d->map[cord.y][cord.x];
			t = ((t_tile *)d->tiles[i]->addr);
			mlx_put_image_to_window(d->mlx, d->win, t->img,
				cord.x * t->width, cord.y * t->height);
		}
		// printf("\n");
	}
}

int	set_img(t_data *d, int mult)
{
	d->tiles = malloc(sizeof(t_tile *) * mult);
	if (!d->tiles)
		return (close_mlx(d));
	d->tiles[0] = create_tile(d->mlx, "img/sky.xpm", "sky");
	d->tiles[1] = create_tile(d->mlx, "img/renga.xpm", "renga");
	d->tiles[2] = create_tile(d->mlx, "img/coin.xpm", "coin");
	d->tiles[3] = create_tile(d->mlx, "img/flag.xpm", "flag");
	d->tiles[4] = create_tile(d->mlx, "img/mario.xpm", "mario");
	enlarge_tiles(d, mult);
	return (0);
}

int	width_chk(t_list *start, t_cordinate *map_size)
{
	t_list		*l;
	t_string	*s;
	size_t		i;

	l = start;
	s = (t_string *)(l->item->addr);
	map_size->x = s->len;
	if (map_size->x < 3)
		return (1);
	i = 0;
	while (++i < map_size->y)
	{
		l = l->next;
		s = (t_string *)(l->item->addr);
		if (map_size->x != s->len)
			return (1); 
	}
	return (0);
}

int	surround_one_chk(t_list *start, t_cordinate *map_size)
{
	t_list		*l;
	t_string	*s;
	size_t		i;

	l = start;
	s = (t_string *)(l->item->addr);
	i = -1;
	while (++i < map_size->x)
		if (s->str[i] != '1')
			return (1);
	i = 0;
	while (++i < map_size->y)
	{
		l = l->next;
		s = (t_string *)(l->item->addr);
		if (s->str[0] != '1' || s->str[s->len - 1] != '1')
			return (1);
	}
	i = -1;
	while (++i < map_size->x)
		if (s->str[i] != '1')
			return (1);
	return (0);
}

int	include_char_chk(t_list *l, t_data *d)
{
	t_cordinate	cord;
	char		c;

	l = l->prev;
	cord.x = -1;
	while (++cord.x < d->map_size.y)
	{
		l = l->next;
		cord.y = -1;
		while (++cord.y < d->map_size.x)
		{
			c = ((t_string *)(l->item->addr))->str[cord.y];
			d->map_inf.c_cnt += (c == 'C');
			d->map_inf.e_cnt += (c == 'E');
			d->map_inf.p_cnt += (c == 'P');
			if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
				return (1);
		}
	}
	if (d->map_inf.c_cnt < 1 || d->map_inf.e_cnt != 1 || d->map_inf.p_cnt != 1)
		return (1);
	return (0);
}

int	get_num(char c)
{
	if (c == '0')
		return (0);
	if (c == '1')
		return (1);
	if (c == 'C')
		return (C);
	if (c == 'E')
		return (E);
	if (c == 'P')
		return (P);
	else
		return (0);
}

void	set_map(t_data *d, t_list *start)
{
	t_cordinate	cord;
	t_list		*l;
	char		c;

	l = start->prev;
	d->map = malloc(sizeof(int *) * d->map_size.y);
	if (!d->map)
		close_mlx(d);
	cord.y = -1;
	while (++cord.y < d->map_size.y)
	{
		l = l->next;
		d->map[cord.y] = malloc(sizeof(int) * d->map_size.x);
		if (!d->map[cord.y])
			close_mlx(d);
		cord.x = -1;
		while (++cord.x < d->map_size.x)
		{
			c = ((t_string *)(l->item->addr))->str[cord.x];
			d->map[cord.y][cord.x] = get_num(c);
		}
	}
}

void	flood_fill_rec(t_cordinate map_size, int **map, size_t y, size_t x)
{
	if (map[y][x] == 1 || map[y][x] >= 10)
		return ;
	if (map[y][x] < 10)
		map[y][x] += 10;
	if (x > 1)
		flood_fill_rec(map_size, map, y, x - 1);
	if (x < map_size.x - 2)
		flood_fill_rec(map_size, map, y, x + 1);
	if (y > 1)
		flood_fill_rec(map_size, map, y - 1, x);
	if (y < map_size.y - 2)
		flood_fill_rec(map_size, map, y + 1, x);
}

void	get_cordinate(t_data *d, t_cordinate *cord, int i)
{
	cord->y = 0;
	while (cord->y < d->map_size.y)
	{
		cord->x = 0;
		while (cord->x < d->map_size.x)
		{
			if (d->map[cord->y][cord->x] == i)
				return ;
			cord->x++;
		}
		cord->y++;
	}
}

int	flood_fill(t_data	*d)
{
	t_cordinate	cord;

	get_cordinate(d, &cord, P);
	flood_fill_rec(d->map_size, d->map, cord.y, cord.x);
	cord.y = -1;
	while (++cord.y < d->map_size.y)
	{
		cord.x = -1;
		while (++cord.x < d->map_size.x)
		{
			if (d->map[cord.y][cord.x] < 10 && d->map[cord.y][cord.x] != 1)
				return (1);
		}
	}
	cord.y = -1;
	while (++cord.y < d->map_size.y)
	{
		cord.x = -1;
		while (++cord.x < d->map_size.x)
		{
			if (d->map[cord.y][cord.x] >= 10)
				d->map[cord.y][cord.x] -= 10;
		}
	}
	return (0);
}

int	check_file(t_item *file, t_data *d)
{
	t_file		*f;
	t_list		*l;

	if (!file)
		return (1);
	f = (t_file *)(file->addr);
	if (!f->lines)
		return (1);
	d->map_size.y = f->line_num;
	if (d->map_size.y < 3)
		return (1);
	l = ((t_list *)(f->lines->addr))->next;
	if (width_chk(l, &d->map_size) || surround_one_chk(l, &d->map_size)
		|| include_char_chk(l, d))
		return (1);
	set_map(d, l);
	if (flood_fill(d))
		return (1);
	return (0);
}

int main(void)
{
	t_data		d;
	int			mult;

	d.mlx = mlx_init();
	d.map_inf.c_cnt = 0;
	d.map_inf.p_cnt = 0;
	d.map_inf.e_cnt = 0;
	mult = 5;
	set_img(&d, mult);
	d.ber = create_file("test.ber", "test");
	if (check_file(d.ber, &d))
		return (write(1, "file error\n", 11), close_mlx(&d), 0);

	d.width = d.map_size.x * mult * 16;
	d.height = d.map_size.y * mult * 16;
	d.win = mlx_new_window(d.mlx, d.width, d.height, "So_long");
	disp_map(&d);
	mlx_hook(d.win, 17, 0, close_mlx, &d);
	mlx_key_hook(d.win, key_event, &d);
	mlx_loop(d.mlx);
	return (0);
}
