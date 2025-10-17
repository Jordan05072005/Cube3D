/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:40:45 by jguaglio          #+#    #+#             */
/*   Updated: 2025/07/13 21:40:45 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_p_c(t_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_groundsky(t_data *d)
{
	size_t	x;
	int		top;
	int		color_top;
	int		color_below;

	color_below = (d->mdata->rgb_f[0] << 16)
		| (d->mdata->rgb_f[1] << 8) | d->mdata->rgb_f[2];
	color_top = (d->mdata->rgb_c[0] << 16)
		| (d->mdata->rgb_c[1] << 8) | d->mdata->rgb_c[2];
	d->img->y = -1;
	top = 1;
	while (++(d->img->y) < (int)d->h)
	{
		x = -1;
		while (++x < d->w)
		{
			if (get_p_c(&d->img[d->i], x, d->img->y) == 0x000000 && top)
				my_mlx_pixel_put_c(&d->img[d->i], x, d, color_top);
			else if (get_p_c(&d->img[d->i], x, d->img->y) == 0x000000 && !top)
				my_mlx_pixel_put_c(&d->img[d->i], x, d, color_below);
			if (d->img->y > (int)d->h / 2)
				top = 0;
		}
	}
}
