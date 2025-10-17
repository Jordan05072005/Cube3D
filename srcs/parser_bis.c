/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:23:00 by jguaglio          #+#    #+#             */
/*   Updated: 2025/10/17 13:23:00 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	mapvalid(char c)
{
	if (c == '1' || c == '0' || c == ' ')
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	return (1);
}

char	*alloc_row_fill(char *src, int w)
{
	char	*row;
	int		j;
	int		len;

	row = (char *)malloc(w + 1);
	if (!row)
		return (NULL);
	len = 0;
	if (src)
		len = (int)ft_strlen(src);
	j = 0;
	while (j < w)
	{
		if (j < len && src[j] != '\0')
			row[j] = src[j];
		else
			row[j] = ' ';
		j++;
	}
	row[w] = '\0';
	return (row);
}

char	**make_square_map(char **maps)
{
	int		h;
	int		w;
	int		i;
	char	**out;

	h = -1;
	w = 0;
	while (maps[++h])
	{
		if ((int)ft_strlen(maps[h]) > w)
			w = (int)ft_strlen(maps[h]);
	}
	out = (char **)malloc(sizeof(char *) * (h + 1));
	if (!out)
		return (NULL);
	i = -1;
	while (++i < h)
	{
		out[i] = alloc_row_fill(maps[i], w);
		if (!out[i])
			return (delstrr(out), NULL);
	}
	out[h] = NULL;
	return (out);
}

int	check_map_closed(char **map, int i)
{
	int	h;
	int	j;
	int	len;

	h = ft_strslen(map);
	while (++i < h)
	{
		len = 0;
		if (map[i])
			len = (int)ft_strlen(map[i]);
		j = -1;
		while (++j < len)
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || j == 0 || i == h - 1 || j == len - 1)
					return (1);
				if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
					map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
					return (1);
			}
		}
	}
	return (0);
}

int	is_player_char(char c)
{
	if (c == 'N')
		return (1);
	if (c == 'S')
		return (1);
	if (c == 'E')
		return (1);
	if (c == 'W')
		return (1);
	return (0);
}
