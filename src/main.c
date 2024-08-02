#include "so_long.h"
#include "ft_lib.h"
#include <stdio.h>

t_data	init(t_data *d)
{
	d->mlx = mlx_init();
	d->width = 1920;
	d->height = 1080;
	d->win = mlx_new_window(d->mlx, d->width, d->height, "So_long");
	return (*d);
}

int main(void)
{
	t_data	d;
	// t_item	*f;
	// int		res;

	init(&d);
	// d.tile = create_tile(d.mlx, "img/renga.xpm", "renga");
	// d.addr = mlx_get_data_addr(d.tile->img, &d.bpp, &d.line_length, &d.endian);
	// d.bpp /= 8;
	// mlx_put_image_to_window(d.mlx, d.win, d.tile->img, 0, 0);
	// f = create_file("Makefile", "make");
	// print_item(f, 1, &res);
	// delete_item(f);

	mlx_hook(d.win, 17, 0, close_mlx, &d);
	mlx_key_hook(d.win, key_event, &d);
	mlx_loop(d.mlx);
	return (0);
}
