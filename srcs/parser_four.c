/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_four.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:26:47 by jguaglio          #+#    #+#             */
/*   Updated: 2025/10/17 13:26:47 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	is_blank(const char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s[i] == '\0');
}

static int	parser_loop(int fd, t_map_data *data, int *lock)
{
	char	*line;
	char	*trim;

	line = get_next_line(fd, 0);
	while (line)
	{
		trim = ft_strtrim(line, " \t\r\n");
		free(line);
		if (!trim)
			return (1);
		if (is_blank(trim) && *lock)
			free(trim);
		else if (is_blank(trim) && !*lock)
		{
			*lock = 2;
			free(trim);
		}
		else if (pars2(data, trim, lock))
		{
			get_next_line(fd, 1);
			return (1);
		}
		line = get_next_line(fd, 0);
	}
	return (0);
}

static int	parser_finish(int fd, t_map_data *data)
{
	int	r;

	close(fd);
	r = pars3(data);
	return (r);
}

int	parser(char *path, t_map_data *data, int lock)
{
	int	fd;
	int	ret;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	ret = parser_loop(fd, data, &lock);
	if (ret)
	{
		close(fd);
		return (1);
	}
	return (parser_finish(fd, data));
}
