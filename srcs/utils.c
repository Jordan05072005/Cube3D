/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:36:15 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 15:36:15 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	max_line(char **maps)
{
	size_t	max;
	int		i;

	max = 0;
	i = -1;
	while (maps[++i])
	{
		if (ft_strlen(maps[i]) > max)
			max = ft_strlen(maps[i]);
	}
	return (max);
}

void	add(double n[2], float r[2])
{
	n[0] = r[0];
	n[1] = r[1];
}

void	set_orientation_from_char(t_map_data *m, char c)
{
	if (c == 'E')
		m->orientation = 0;
	else if (c == 'N')
		m->orientation = 3 * M_PI / 2;
	else if (c == 'S')
		m->orientation = M_PI / 2;
	else if (c == 'W')
		m->orientation = M_PI;
}

void	dest(t_data *d)
{
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mini->win)
		mlx_destroy_window(d->mlx, d->mini->win);
	if (d->img[0].img_ptr)
		mlx_destroy_image(d->mlx, d->img[0].img_ptr);
	if (d->img[1].img_ptr)
		mlx_destroy_image(d->mlx, d->img[1].img_ptr);
	if (d->tex[0].tex)
		mlx_destroy_image(d->mlx, d->tex[0].tex);
	if (d->tex[1].tex)
		mlx_destroy_image(d->mlx, d->tex[1].tex);
	if (d->tex[2].tex)
		mlx_destroy_image(d->mlx, d->tex[2].tex);
	if (d->tex[3].tex)
		mlx_destroy_image(d->mlx, d->tex[3].tex);
	if (d->mlx)
		mlx_destroy_display(d->mlx);
}

int	is_digit_str(const char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}
