/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:50:01 by retanaka          #+#    #+#             */
/*   Updated: 2024/07/18 16:50:03 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	success(t_data *d)
{
	write(1, "You did it!\n", 12);
	close_mlx(d);
	exit(0);
}

int	error(t_data *d, char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	close_mlx(d);
	exit(1);
	return (1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	ones_place;

	if (n == INT_MIN)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		if (n < 0)
			n = ~n + write(fd, "-", 1);
		ones_place = (n % 10) + '0';
		n /= 10;
		if (n > 0)
			ft_putnbr_fd(n, fd);
		write (fd, &ones_place, 1);
	}
}

int	close_mlx(t_data *d)
{
	size_t	i;

	i = -1;
	while (++i < 5)
		delete(d->tiles[i]);
	free(d->tiles);
	i = -1;
	if (d->map)
	{
		while (++i < d->map_size.y)
			if (d->map[i])
				free(d->map[i]);
		free(d->map);
	}
	mlx_loop_end(d->mlx);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	return (0);
}

int	key_event(int key, t_data *d)
{
	if (key == ESC)
		return (close_mlx(d), exit(0), 0);
	if (key == UP || key == UP_W || key == DOWN || key == DOWN_S
		|| key == LEFT || key == LEFT_A || key == RIGHT || key == RIGHT_D)
		update_map(d, key);
	return (0);
}
