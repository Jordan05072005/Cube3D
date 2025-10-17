/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_final.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:29:00 by jguaglio          #+#    #+#             */
/*   Updated: 2025/10/17 13:29:00 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	header_texture(t_map_data *d, char **p)
{
	if (!p[1] || !*p[1])
		return (error_mess("Texture path missing"), 1);
	if (!ft_strncmp(p[0], "NO", 3) && d->path_n)
		return (error_mess("Duplicate NO"), 1);
	if (!ft_strncmp(p[0], "SO", 3) && d->path_s)
		return (error_mess("Duplicate SO"), 1);
	if (!ft_strncmp(p[0], "WE", 3) && d->path_w)
		return (error_mess("Duplicate WE"), 1);
	if (!ft_strncmp(p[0], "EA", 3) && d->path_e)
		return (error_mess("Duplicate EA"), 1);
	fill_texture(p[0], p[1], d);
	if ((!ft_strncmp(p[0], "NO", 3) && !d->path_n)
		|| (!ft_strncmp(p[0], "SO", 3) && !d->path_s)
		|| (!ft_strncmp(p[0], "WE", 3) && !d->path_w)
		|| (!ft_strncmp(p[0], "EA", 3) && !d->path_e))
		return (1);
	return (0);
}

static int	header_rgb(t_map_data *d, char **p)
{
	if (!p[1] || !*p[1])
		return (error_mess("RGB missing"), 1);
	if (p[0][0] == 'F' && d->rgb_f)
		return (error_mess("Duplicate F"), 1);
	if (p[0][0] == 'C' && d->rgb_c)
		return (error_mess("Duplicate C"), 1);
	if (p[0][0] == 'F')
		fill_rgb("F", p[1], d);
	else
		fill_rgb("C", p[1], d);
	if ((p[0][0] == 'F' && !d->rgb_f) || (p[0][0] == 'C' && !d->rgb_c))
		return (1);
	return (0);
}

static int	pars2_header(t_map_data *d, char *trim)
{
	char	**p;
	int		ret;

	p = ft_split(trim, ' ');
	if (!p || !p[0])
		return (delstrr(p), free(trim), error_mess("Bad header"), 1);
	if (is_texture_id(p[0]))
		ret = header_texture(d, p);
	else if ((p[0][0] == 'F' && !p[0][1]) || (p[0][0] == 'C' && !p[0][1]))
		ret = header_rgb(d, p);
	else
		ret = (error_mess("Unknown header id"), 1);
	if (p)
		delstrr(p);
	free(trim);
	return (ret);
}

static int	pars2_mapline(t_map_data *d, char *trim, int *lock)
{
	char	*line;
	char	*base;

	if (*lock == 2)
		return (free(trim), error_mess("Empty line in map"), 1);
	*lock = 0;
	line = ft_strjoin(trim, "\n");
	if (!line)
		return (free(trim), 1);
	base = d->tmaps;
	d->tmaps = ft_strjoinf2(base, line);
	free(trim);
	if (!d->tmaps)
		return (1);
	return (0);
}

int	pars2(t_map_data *d, char *trim, int *lock)
{
	if (*trim && ft_isdigit((unsigned char)trim[0]))
		return (pars2_mapline(d, trim, lock));
	if (*trim)
		return (pars2_header(d, trim));
	free(trim);
	return (0);
}
