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
	d->tiles = malloc(sizeof(t_tile *) * 5);
	if (!d->tiles)
		return (close_mlx(d));
	d->tiles[0] = create_tile(d->mlx, "texture/sky.xpm", "sky");
	d->tiles[1] = create_tile(d->mlx, "texture/renga.xpm", "renga");
	d->tiles[2] = create_tile(d->mlx, "texture/coin.xpm", "coin");
	d->tiles[3] = create_tile(d->mlx, "texture/flag.xpm", "flag");
	d->tiles[4] = create_tile(d->mlx, "texture/mario.xpm", "mario");
	enlarge_tiles(d, mult);
	return (0);
}

void	data_init(t_data *d)
{
	d->mlx = NULL;
	d->win = NULL;
	d->addr = NULL;
	d->tiles = NULL;
	d->width = 0;
	d->height = 0;
	d->ber = NULL;
	d->map = NULL;
	d->map_size.y = 0;
	d->map_size.x = 0;
	d->map_inf.p_cnt = 0;
	d->map_inf.c_cnt = 0;
	d->map_inf.e_cnt = 0;
	d->player_move = 0;
	d->get_coin = 0;
}

int	main(void)
{
	t_data		d;
	int			mult;

	data_init(&d);
	d.mlx = mlx_init();
	mult = 3;
	set_img(&d, mult);
	d.ber = create_file("maps/test.ber", "test");
	if (check_file(&d))
		return (close_mlx(&d), 0);
	d.width = d.map_size.x * mult * 16;
	d.height = d.map_size.y * mult * 16;
	d.win = mlx_new_window(d.mlx, d.width, d.height, "So_long");
	disp_map(&d);
	mlx_hook(d.win, 17, 0, close_mlx, &d);
	mlx_key_hook(d.win, key_event, &d);
	mlx_loop(d.mlx);
	return (0);
}
