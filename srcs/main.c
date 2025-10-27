/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:31 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:31 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	on_keydown(int keycode, t_data *d)
{
	if (keycode == KEY_W || keycode == KEY_Z)
		d->keys.w = 1;
	else if (keycode == KEY_A || keycode == KEY_Q)
		d->keys.a = 1;
	else if (keycode == KEY_S)
		d->keys.s = 1;
	else if (keycode == KEY_D)
		d->keys.d = 1;
	else if (keycode == KEY_LEFT)
		d->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		d->keys.right = 1;
	else if (keycode == KEY_ESC)
		d->keys.esc = 1;
	return (0);
}

int	on_keyup(int keycode, t_data *d)
{
	if (keycode == KEY_W || keycode == KEY_Z)
		d->keys.w = 0;
	else if (keycode == KEY_A || keycode == KEY_Q)
		d->keys.a = 0;
	else if (keycode == KEY_S)
		d->keys.s = 0;
	else if (keycode == KEY_D)
		d->keys.d = 0;
	else if (keycode == KEY_LEFT)
		d->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		d->keys.right = 0;
	else if (keycode == KEY_ESC)
		d->keys.esc = 0;
	return (0);
}

void	close_program(t_data *d)
{
	dest(d);
	free(d->mlx);
	free(d->img);
	free(d->mdata->path_e);
	free(d->mdata->path_n);
	free(d->mdata->path_w);
	free(d->mdata->path_s);
	free(d->mdata->rgb_c);
	free(d->mdata->rgb_f);
	free(d->mdata->player);
	free(d->mdata->tmaps);
	delstrr(d->mdata->maps);
	free(d->mdata);
	free(d->mini);
	free(d);
	exit(0);
}

int	on_destroy(t_data *d)
{
	return (close_program(d), 1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (error_mess("Number of arguments"), 1);
	data = init_data(1000, 600);
	if (!data)
		return (1);
	if (parser(argv[1], data->mdata, 1))
		return (error_mess("I can't open file"), close_program(data), 1);
	if (error_handling(data->mdata))
		return (error_mess("Maps incorrect"), close_program(data), 1);
	if (fill_info(data))
		return (close_program(data), 1);
	data->oldt = 0;
	draw_minmaps(data->mdata, data);
	mlx_hook(data->win, ON_KEYDOWN, 1L << 0, on_keydown, data);
	mlx_hook(data->win, ON_KEYUP, 1L << 1, on_keyup, data);
	mlx_hook(data->win, ON_DESTROY, 0, on_destroy, data);
	mlx_loop_hook(data->mlx, move, data);
	mlx_loop(data->mlx);
}
