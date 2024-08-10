/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:08:25 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 15:08:26 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	main(void)
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
