/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:28 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:28 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_map_data	*init_map_data(void)
{
	t_map_data	*data;

	data = malloc(sizeof(t_map_data));
	data->tmaps = NULL;
	data->path_e = NULL;
	data->path_w = NULL;
	data->path_n = NULL;
	data->path_s = NULL;
	data->rgb_c = 0;
	data->rgb_f = 0;
	data->player = 0;
	return (data);
}

void	*init_img(t_data *d)
{
	d->img = malloc(sizeof(t_img) * 2);
	if (!d->img)
		return (NULL);
	d->img[0].img_ptr = mlx_new_image(d->mlx, d->w, d->h);
	d->img[1].img_ptr = mlx_new_image(d->mlx, d->w, d->h);
	d->img[0].addr = mlx_get_data_addr(d->img[0].img_ptr, &d->img[0].bpp,
			&d->img[0].line_len, &d->img[0].endian);
	d->img[1].addr = mlx_get_data_addr(d->img[1].img_ptr, &d->img[1].bpp,
			&d->img[1].line_len, &d->img[1].endian);
	return (NULL);
}

void	in(t_data *d)
{
	d->tex[0].tex = NULL;
	d->tex[1].tex = NULL;
	d->tex[2].tex = NULL;
	d->tex[3].tex = NULL;
}

t_data	*init_data(size_t l, size_t h)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	d->mini = malloc(sizeof(t_mini_map));
	d->mlx = mlx_init();
	if (!d->mlx)
		return (NULL);
	d->w = l;
	d->h = h;
	d->mini->win = mlx_new_window(d->mlx, l, h, "Cub3D MiniMap");
	d->win = mlx_new_window(d->mlx, l, h, "Cub3D");
	d->mdata = init_map_data();
	d->mdata->maps = NULL;
	in(d);
	init_img(d);
	d->i = 0;
	d->keys.w = 0;
	d->keys.a = 0;
	d->keys.s = 0;
	d->keys.d = 0;
	d->keys.esc = 0;
	d->keys.left = 0;
	d->keys.right = 0;
	return (d);
}

void	init(int *lst, size_t s, int init)
{
	int	i;

	i = -1;
	while (++i < (int)s)
		lst[i] = init;
}
