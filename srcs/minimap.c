/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:20 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:20 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_rect(size_t size[2], int yb, int xb, t_data *d)
{
	size_t	x;
	size_t	y;

	y = size[1] * yb;
	while (++y < (size[1] * (yb + 1)))
	{
		x = size[0] * xb;
		while (++x < (size[0] * (1 + xb)))
			mlx_pixel_put(d->mlx, d->mini->win, x, y, 0xFF0000);
	}
}

void	draw_circle(t_data *d, int x0, int y0, int color)
{
	int	x;
	int	y;
	int	r;

	r = d->mdata->hitbox;
	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
				mlx_pixel_put(d->mlx, d->mini->win, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

void	draw_minmaps(t_map_data *m, t_data *d)
{
	int	x;
	int	y;

	y = -1;
	while (m->maps[++y])
	{
		x = -1;
		while (m->maps[y][++x])
		{
			if (m->maps[y][x] == '1')
				draw_rect(m->size_bloc, y, x, d);
		}
	}
}

void	draw_player(t_map_data *m, t_data *d, float co[2], int color)
{
	if (color != 0x000000)
		draw_player(m, d, m->old_co, 0x000000);
	draw_circle(d, co[0], co[1], color);
}
