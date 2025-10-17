/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabatail <pabatail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:31:13 by pabatail          #+#    #+#             */
/*   Updated: 2025/10/09 14:38:27 by pabatail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_map_data(t_map_data *m)
{
	if (!m)
		return ;
	free_map_strings(m);
	if (m->rgb_f)
		free(m->rgb_f);
	if (m->rgb_c)
		free(m->rgb_c);
	if (m->player)
		free(m->player);
	m->rgb_f = NULL;
	m->rgb_c = NULL;
	m->player = NULL;
	free(m);
}

static void	free_images_and_textures(t_data *d)
{
	int	i;

	if (!d)
		return ;
	i = 0;
	while (i < 4)
	{
		if (d->tex[i].tex)
			mlx_destroy_image(d->mlx, d->tex[i].tex);
		d->tex[i].tex = NULL;
		i++;
	}
	if (d->img)
	{
		i = 0;
		while (i < 2)
		{
			if (d->img[i].img_ptr)
				mlx_destroy_image(d->mlx, d->img[i].img_ptr);
			i++;
		}
		free(d->img);
		d->img = NULL;
	}
}

static void	free_windows_and_mlx(t_data *d)
{
	if (!d)
		return ;
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mini && d->mini->win)
		mlx_destroy_window(d->mlx, d->mini->win);
	if (d->mini)
		free(d->mini);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free(d->mlx);
		d->mlx = NULL;
	}
}

void	free_data(t_data *d)
{
	if (!d)
		return ;
	free_images_and_textures(d);
	free_map_data(d->mdata);
	free_windows_and_mlx(d);
	free(d);
}
