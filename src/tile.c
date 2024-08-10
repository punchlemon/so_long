/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retanaka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 15:27:16 by retanaka          #+#    #+#             */
/*   Updated: 2024/08/10 15:27:17 by retanaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	enlarge_img(t_tile *t, void *new_img, unsigned int m)
{
	int			w;
	t_cordinate	c;
	t_cordinate	c2;
	int			*new;
	int			*old;

	new = (int *)mlx_get_data_addr(new_img, &w, &w, &w);
	old = (int *)mlx_get_data_addr(t->img, &w, &w, &w);
	w = t->width * m;
	c.y = -1;
	while (++c.y < (unsigned int)t->height)
	{
		c.x = -1;
		while (++c.x < (unsigned int)t->width)
		{
			c2.y = -1;
			while (++c2.y < m)
			{
				c2.x = -1;
				while (++c2.x < m)
					(new + (c.y * w + c.x) * m)[c2.y * w + c2.x]
						= old[c.y * t->width + c.x];
			}
		}
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
