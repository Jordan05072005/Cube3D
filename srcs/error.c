/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:23 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:23 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	error_handling2(t_map_data *data)
{
	if (!data->path_e || !data->path_w || !data->path_s
		|| !data->path_w || data->rgb_c == 0 || !data->rgb_f
		|| data->player == 0)
		return (1);
	return (0);
}

int	error_handling(t_map_data *data)
{
	int	i;
	int	j;
	int	l[2];

	i = -1;
	while (data->maps[++i])
	{
		j = -1;
		init(l, 2, -1);
		while (data->maps[i][++j])
		{
			if (((i == 0 || i == (ft_strslen(data->maps) - 1))
					&& (data->maps[i][j] != 32 && data->maps[i][j] != '1'))
				|| mapvalid(data->maps[i][j]))
				return (1);
			if (l[0] == -1 && data->maps[i][j] != 32)
				l[0] = data->maps[i][j];
			if (data->maps[i][j] != 32)
				l[1] = data->maps[i][j];
		}
		if (l[0] != '1' || l[1] != '1')
			return (1);
	}
	return (error_handling2(data));
}

void	error_mess(char *mess)
{
	ft_putstr_fd("Error : \n", 2);
	ft_putstr_fd(mess, 2);
	ft_putstr_fd("\n", 2);
}
