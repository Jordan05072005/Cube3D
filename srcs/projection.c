/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:15:03 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/17 09:15:03 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_wall(t_data *d, t_casting *c, int x, t_tex tex)
{
	double	di;
	double	h;
	double	y;
	double	step;
	double	t;

	t = tex.y;
	di = c->pas * cos(c->angle - d->mdata->orientation);
	if (di < 0.0001)
		di = 0.0001;
	h = (d->mdata->size_bloc[1] / di) * ((d->h / 4) / tan(d->mdata->fov));
	y = (int)ceil((d->h / 2) - h / 2);
	step = tex.h / h;
	while (y < (d->h / 2) + h / 2 && y < d->h)
	{
		d->img->y = y;
		my_mlx_pixel_put(&d->img[d->i], &tex, x, d);
		t += step;
		tex.y = t;
		if (tex.y >= tex.h)
			t = 0;
		y++;
	}
}

t_tex	choise_tex(t_casting c, t_data *d, double xy[2], int t)
{
	c.sz[0] = d->mdata->size_bloc[0];
	c.sz[1] = d->mdata->size_bloc[1];
	c.lc[0] = fmod(xy[0], c.sz[0]);
	c.lc[1] = fmod(xy[1], c.sz[1]);
	if (c.lc[0] < 0.0)
		c.lc[0] += c.sz[0];
	if (c.lc[1] < 0.0)
		c.lc[1] += c.sz[1];
	if (fabs(c.lc[0]) < c.ray_step || fabs(c.lc[0] - c.sz[0]) < c.ray_step)
	{
		if (!(fabs(c.lc[0]) < c.ray_step))
			t = (t + 2) % 4;
		d->tex[t].x = (int)((c.lc[1] / c.sz[1]) * d->tex->w);
	}
	else
	{
		if (fabs(c.lc[1]) < c.ray_step)
			t = (t + 1) % 4;
		else
			t = (t + 3) % 4;
		d->tex[t].x = (int)((c.lc[0] / c.sz[0]) * d->tex->w);
	}
	d->tex[t].y = 0;
	return (d->tex[t]);
}

void	fillc(t_casting *c, t_data *d, int *i, int x)
{
	c->r = (double)x / d->w;
	c->angle = d->mdata->orientation
		- d->mdata->fov + (2 * d->mdata->fov * c->r);
	c->pas = 0;
	c->ray_step = 1;
	*i = 0;
}

void	draw_projection(t_data *d)
{
	t_casting	c;
	double		xy[2];
	size_t		x;
	int			i;

	x = -1;
	while (++x < d->w)
	{
		fillc(&c, d, &i, x);
		while (i++ < 2)
		{
			xy[0] = d->mdata->co[0] + cos(c.angle) * c.pas;
			xy[1] = d->mdata->co[1] + sin(c.angle) * c.pas;
			while (!collision_wall(xy[0], xy[1], d->mdata, d))
			{
				xy[0] = d->mdata->co[0] + cos(c.angle) * c.pas;
				xy[1] = d->mdata->co[1] + sin(c.angle) * c.pas;
				c.pas += c.ray_step;
			}
			c.pas -= (c.ray_step * 2);
			c.ray_step = 0.1;
		}
		draw_wall(d, &c, x, choise_tex(c, d, xy, 0));
	}
}
