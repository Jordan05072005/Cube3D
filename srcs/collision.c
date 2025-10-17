/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:49:13 by jguaglio          #+#    #+#             */
/*   Updated: 2025/09/18 18:42:00 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	is_block_cell(t_map_data *m, int gy, int gx)
{
	if (gy < 0 || gx < 0)
		return (1);
	if (gy >= (int)ft_strslen(m->maps))
		return (1);
	if (gx >= (int)ft_strlen(m->maps[gy]))
		return (1);
	if (m->maps[gy][gx] == '1' || m->maps[gy][gx] == ' ')
		return (1);
	return (0);
}

int	collision_wall(double x, double y, t_map_data *m, t_data *d)
{
	int	gx;
	int	gy;

	(void)d;
	gx = (int)(x / (double)m->size_bloc[0]);
	gy = (int)(y / (double)m->size_bloc[1]);
	return (is_block_cell(m, gy, gx));
}

int	collision_player(double x, double y, t_map_data *m, t_data *d)
{
	int		gx[5];
	int		gy[5];
	int		h;
	int		i;

	(void)d;
	h = m->hitbox;
	gx[0] = (int)((x - h) / (double)m->size_bloc[0]);
	gy[0] = (int)(y / (double)m->size_bloc[1]);
	gx[1] = (int)(x / (double)m->size_bloc[0]);
	gy[1] = (int)((y - h) / (double)m->size_bloc[1]);
	gx[2] = (int)((x + h) / (double)m->size_bloc[0]);
	gy[2] = (int)(y / (double)m->size_bloc[1]);
	gx[3] = (int)(x / (double)m->size_bloc[0]);
	gy[3] = (int)((y + h) / (double)m->size_bloc[1]);
	gx[4] = (int)(x / (double)m->size_bloc[0]);
	gy[4] = (int)(y / (double)m->size_bloc[1]);
	i = -1;
	while (++i < 5)
		if (is_block_cell(m, gy[i], gx[i]))
			return (1);
	return (0);
}
