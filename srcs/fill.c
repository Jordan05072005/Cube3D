/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:16:12 by jguaglio          #+#    #+#             */
/*   Updated: 2025/08/30 16:16:12 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	fill_tex(t_data *d)
{
	d->tex[0].tex = mlx_xpm_file_to_image(d->mlx,
			d->mdata->path_s, &d->tex[0].w, &d->tex[0].h);
	if (!d->tex[0].tex)
		return (write(2, "Erreur XPM\n", 11), 1);
	d->tex[0].data = mlx_get_data_addr(d->tex[0].tex,
			&d->tex[0].bpp, &d->tex[0].size_line, &d->tex[0].endian);
	d->tex[1].tex = mlx_xpm_file_to_image(d->mlx,
			d->mdata->path_e, &d->tex[1].w, &d->tex[1].h);
	if (!d->tex[1].tex)
		return (write(2, "Erreur XPM\n", 11), 1);
	d->tex[1].data = mlx_get_data_addr(d->tex[1].tex,
			&d->tex[1].bpp, &d->tex[1].size_line, &d->tex[1].endian);
	d->tex[2].tex = mlx_xpm_file_to_image(d->mlx,
			d->mdata->path_w, &d->tex[2].w, &d->tex[2].h);
	if (!d->tex[2].tex)
		return (write(2, "Erreur XPM\n", 11), 1);
	d->tex[2].data = mlx_get_data_addr(d->tex[2].tex,
			&d->tex[2].bpp, &d->tex[2].size_line, &d->tex[2].endian);
	d->tex[3].tex = mlx_xpm_file_to_image(d->mlx,
			d->mdata->path_n, &d->tex[3].w, &d->tex[3].h);
	if (!d->tex[3].tex)
		return (write(2, "Erreur XPM\n", 11), 1);
	d->tex[3].data = mlx_get_data_addr(d->tex[3].tex,
			&d->tex[3].bpp, &d->tex[3].size_line, &d->tex[3].endian);
	return (0);
}

int	fill_info(t_data *d)
{
	d->mdata->size_bloc[0] = d->w / max_line(d->mdata->maps);
	d->mdata->size_bloc[1] = d->h / ft_strslen(d->mdata->maps);
	d->mdata->co[0] = d->mdata->player[0] * d->mdata->size_bloc[0]
		+ (d->mdata->size_bloc[0] / 2);
	d->mdata->co[1] = d->mdata->player[1] * d->mdata->size_bloc[1]
		+ (d->mdata->size_bloc[1] / 2);
	d->mdata->old_co[0] = d->mdata->player[0] * d->mdata->size_bloc[0]
		+ (d->mdata->size_bloc[0] / 2);
	d->mdata->old_co[1] = d->mdata->player[1] * d->mdata->size_bloc[1]
		+ (d->mdata->size_bloc[1] / 2);
	d->keycode = 0;
	if (fill_tex(d))
		return (1);
	d->mdata->fov = M_PI / 6;
	if (d->mdata->orientation == 'W')
		d->mdata->orientation = 0;
	else if (d->mdata->orientation == 'S')
		d->mdata->orientation = (3 * M_PI) / 2;
	else if (d->mdata->orientation == 'O')
		d->mdata->orientation = M_PI;
	else if (d->mdata->orientation == 'N')
		d->mdata->orientation = M_PI / 2;
	d->mdata->vel = 2;
	d->mdata->hitbox = 5;
	return (0);
}
