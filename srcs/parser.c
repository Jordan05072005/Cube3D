/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <jguaglio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:35 by jguaglio          #+#    #+#             */
/*   Updated: 2025/10/09 22:40:00 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static char	*trim_copy(char *s)
{
	char	*t;
	char	*r;

	t = ft_strtrim(s, " \t\r");
	if (!t)
		return (NULL);
	r = ft_strdup(t);
	free(t);
	return (r);
}

int	pars_rgb_triplet_two(t_var v, long **dst_rgb)
{
	if (v.r < 0 || v.r > 255 || v.g < 0 || v.g > 255 || v.bl < 0 || v.bl > 255)
		return (1);
	*dst_rgb = (long *)malloc(sizeof(long) * 3);
	if (!*dst_rgb)
		return (1);
	(*dst_rgb)[0] = v.r;
	(*dst_rgb)[1] = v.g;
	(*dst_rgb)[2] = v.bl;
	return (0);
}

int	parse_rgb_triplet(char *other, long **dst_rgb)
{
	t_var	v;

	v.v = ft_split(other, ',');
	if (!v.v || ft_strslen(v.v) != 3 || other[ft_strlen(other) - 1] == ',')
		return (delstrr(v.v), 1);
	v.a = trim_copy(v.v[0]);
	v.b = trim_copy(v.v[1]);
	v.c = trim_copy(v.v[2]);
	if (!v.a || !v.b || !v.c)
		return (free(v.a), free(v.b), free(v.c), delstrr(v.v), 1);
	if (!is_digit_str(v.a) || !is_digit_str(v.b) || !is_digit_str(v.c))
		return (free(v.a), free(v.b), free(v.c), delstrr(v.v), 1);
	v.r = ft_atoi(v.a);
	v.g = ft_atoi(v.b);
	v.bl = ft_atoi(v.c);
	free(v.a);
	free(v.b);
	free(v.c);
	delstrr(v.v);
	return (pars_rgb_triplet_two(v, dst_rgb));
}

void	fill_texture(char *id, char *other, t_map_data *d)
{
	char	*p;

	if (!other)
	{
		error_mess("Texture path missing");
		return ;
	}
	p = ft_strdup(other);
	if (!p)
		return ;
	if (!ft_strncmp(id, "NO", 3))
		d->path_n = p;
	else if (!ft_strncmp(id, "SO", 3))
		d->path_s = p;
	else if (!ft_strncmp(id, "WE", 3))
		d->path_w = p;
	else if (!ft_strncmp(id, "EA", 3))
		d->path_e = p;
}

void	fill_rgb(char *id, char *other, t_map_data *d)
{
	if (!id || !other)
		return ;
	if (id[0] == 'F')
	{
		if (d->rgb_f || parse_rgb_triplet(other, &d->rgb_f))
			error_mess("Invalid/duplicate floor RGB");
	}
	else if (id[0] == 'C')
	{
		if (d->rgb_c || parse_rgb_triplet(other, &d->rgb_c))
			error_mess("Invalid/duplicate ceiling RGB");
	}
}
