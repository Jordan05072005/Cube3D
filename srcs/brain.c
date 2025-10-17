/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabatail <pabatail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:21:27 by pabatail          #+#    #+#             */
/*   Updated: 2025/09/18 16:21:27 by pabatail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"
#include <sys/time.h>
#include <math.h>

// double adjust_x(t_map_data *m, int hitbox)
// {
// 	return (m->co[0] + cos(m->orientation) * (m->vel));
// }

// double adjust_y(t_map_data *m, int hitbox)
// {
// 	return (m->co[1] + sin(m->orientation) * (m->vel));
// }

static void	try_move_xy(t_data *d, double nx, double ny)
{
	if (!collision_player(nx, d->mdata->co[1], d->mdata, d))
		d->mdata->co[0] = (int)llround(nx);
	if (!collision_player(d->mdata->co[0], ny, d->mdata, d))
		d->mdata->co[1] = (int)llround(ny);
}

void	handle_movement(t_data *d, double s, double cx, double sx)
{
	double	n[2];

	add(n, d->mdata->co);
	if (d->keys.w)
	{
		n[0] += cx * s;
		n[1] += sx * s;
	}
	else if (d->keys.s)
	{
		n[0] -= cx * s;
		n[1] -= sx * s;
	}
	else if (d->keys.a)
	{
		n[0] += sx * s;
		n[1] -= cx * s;
	}
	else if (d->keys.d)
	{
		n[0] -= sx * s;
		n[1] += cx * s;
	}
	try_move_xy(d, n[0], n[1]);
}

void	handle_rotation(t_data *d)
{
	double	rot;

	rot = M_PI / 72.0;
	if (d->keys.left)
		d->mdata->orientation -= rot;
	if (d->keys.right)
		d->mdata->orientation += rot;
	if (d->mdata->orientation >= 2 * M_PI)
		d->mdata->orientation -= 2 * M_PI;
	else if (d->mdata->orientation < 0)
		d->mdata->orientation += 2 * M_PI;
}

static void	nudge_off_wall(t_data *d)
{
	double	eps;
	int		tries;
	double	ang;
	double	bx;
	double	by;

	tries = 4;
	eps = 0.001;
	while (tries-- && collision_player(d->mdata->co[0],
			d->mdata->co[1], d->mdata, d))
	{
		ang = d->mdata->orientation;
		bx = d->mdata->co[0] - cos(ang) * eps * d->mdata->size_bloc[0];
		by = d->mdata->co[1] - sin(ang) * eps * d->mdata->size_bloc[1];
		if (!collision_player(bx, d->mdata->co[1], d->mdata, d))
			d->mdata->co[0] = (int)llround(bx);
		if (!collision_player(d->mdata->co[0], by, d->mdata, d))
			d->mdata->co[1] = (int)llround(by);
	}
}

int	move(void *p)
{
	t_map_data	*m;
	t_data		*d;

	d = (t_data *)p;
	m = d->mdata;
	if (d->mdata->old_co[0] != d->mdata->co[0]
		|| d->mdata->old_co[1] != d->mdata->co[1])
		draw_player(m, d, m->co, 0x000000);
	if (d->keys.esc)
		return (close_program(d), 1);
	handle_rotation(d);
	handle_movement(d, d->mdata->vel,
		cos(d->mdata->orientation), sin(d->mdata->orientation));
	nudge_off_wall(d);
	draw_groundsky(d);
	draw_projection(d);
	draw_minmaps(d->mdata, d);
	draw_player(m, d, m->co, 0x00FF00);
	apply_frame(d, &d->img[d->i]);
	return (0);
}
