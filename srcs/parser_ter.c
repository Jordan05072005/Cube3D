/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:27:33 by jguaglio          #+#    #+#             */
/*   Updated: 2025/10/17 13:27:33 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	set_player_from_cell(t_map_data *m, int y, int x)
{
	int	*pos;

	pos = (int *)malloc(sizeof(int) * 2);
	if (!pos)
		return (1);
	pos[0] = x;
	pos[1] = y;
	m->player = pos;
	set_orientation_from_char(m, m->maps[y][x]);
	m->maps[y][x] = '0';
	return (0);
}

int	find_player(t_map_data *m)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = 0;
	while (m->maps[i])
	{
		j = 0;
		while (m->maps[i][j])
		{
			if (is_player_char(m->maps[i][j]))
			{
				if (found == 1 || set_player_from_cell(m, i, j))
					return (1);
				found = 1;
			}
			j++;
		}
		i++;
	}
	if (found == 0)
		return (1);
	return (0);
}

int	validate_chars_block(char **m)
{
	int	y;
	int	x;

	y = 0;
	while (m[y])
	{
		x = 0;
		while (m[y][x])
		{
			if (mapvalid(m[y][x]))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	pars3(t_map_data *data)
{
	char	**sq;

	if (!data->tmaps)
		return (1);
	data->maps = ft_split(data->tmaps, '\n');
	if (!data->maps)
		return (1);
	sq = make_square_map(data->maps);
	if (!sq)
		return (delstrr(data->maps), 1);
	delstrr(data->maps);
	data->maps = sq;
	if (validate_chars_block(data->maps))
		return (1);
	if (check_map_closed(data->maps, -1) || find_player(data))
		return (1);
	return (0);
}

int	is_texture_id(const char *s)
{
	if (!ft_strncmp(s, "NO", 3))
		return (1);
	if (!ft_strncmp(s, "SO", 3))
		return (1);
	if (!ft_strncmp(s, "WE", 3))
		return (1);
	if (!ft_strncmp(s, "EA", 3))
		return (1);
	return (0);
}
