/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <jguaglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:00:00 by jguaglio          #+#    #+#             */
/*   Updated: 2025/10/07 12:00:00 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	delstrr(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_del(char **str)
{
	if (!str)
		return ;
	if (*str)
		free(*str);
	*str = NULL;
}

char	*ft_replace(char *str, char *replace)
{
	ft_del(&str);
	str = replace;
	return (str);
}

void	free_map_strings(t_map_data *m)
{
	ft_del(&m->path_n);
	ft_del(&m->path_s);
	ft_del(&m->path_w);
	ft_del(&m->path_e);
	ft_del(&m->tmaps);
	if (m->maps)
		delstrr(m->maps);
	m->maps = NULL;
}
