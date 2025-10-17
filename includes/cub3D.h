/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 19:52:37 by jguaglio          #+#    #+#             */
/*   Updated: 2025/10/06 19:52:37 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <signal.h>

# define M_PI 3.14159265358979323846

# ifdef __APPLE__
#  define KEY_W     13
#  define KEY_A      0
#  define KEY_S      1
#  define KEY_D      2
#  define KEY_Q     12
#  define KEY_Z      6
#  define KEY_ESC   53
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_Q 113
#  define KEY_Z 122
#  define KEY_ESC 65307
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
# endif

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_DESTROY 17

typedef struct s_var
{
	char	**v;
	char	*a;
	char	*b;
	char	*c;
	long	r;
	long	g;
	long	bl;
}	t_var;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_keys;

typedef struct s_map_data
{
	char		*path_n;
	char		*path_s;
	char		*path_w;
	char		*path_e;
	long		*rgb_f;
	long		*rgb_c;
	char		*tmaps;
	char		**maps;
	int			*player;
	double		vel;
	int			hitbox;
	double		fov;
	double		orientation;
	size_t		size_bloc[2];
	float		co[2];
	float		old_co[2];
}					t_map_data;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		y;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mini_map
{
	void	*win;
	size_t	w;
	size_t	h;
}	t_mini_map;

typedef struct s_texture
{
	void	*tex;
	char	*data;
	int		bpp;
	int		size_line;
	int		x;
	int		y;
	int		w;
	int		h;
	int		endian;
}	t_tex;

typedef struct s_casting
{
	double	angle;
	double	r;
	double	ray_step;
	double	pas;
	double	sz[2];
	double	lc[2];
}	t_casting;

typedef struct data
{
	void		*mlx;
	void		*win;
	int			keycode;
	size_t		w;
	size_t		h;
	t_img		*img;
	t_tex		tex[4];
	int			i;
	t_mini_map	*mini;
	t_map_data	*mdata;
	t_keys		keys;
}	t_data;

// free.c
void		delstrr(char **str);
void		ft_del(char **str);
char		*ft_replace(char *str, char *replace);
void		free_data(t_data *d);
void		free_map_data(t_map_data *m);
void		free_map_strings(t_map_data *m);

// parser.c
void		fill_rgb(char *id, char *other, t_map_data *data);
void		fill_texture(char *id, char *other, t_map_data *data);
int			parse_rgb_triplet(char *other, long **dst_rgb);
int			is_digit_str(const char *s);
int			parser(char *path, t_map_data *data, int lock);
int			mapvalid(char c);
void		set_orientation_from_char(t_map_data *m, char c);
int			is_player_char(char c);
int			check_map_closed(char **map, int i);
char		**make_square_map(char **maps);
char		*alloc_row_fill(char *src, int w);
int			set_player_from_cell(t_map_data *m, int y, int x);
int			pars3(t_map_data *data);
int			pars2(t_map_data *data, char *trim, int *lock);
int			is_texture_id(const char *s);
int			pars3(t_map_data *data);
int			validate_chars_block(char **m);
int			find_player(t_map_data *m);
int			set_player_from_cell(t_map_data *m, int y, int x);

// error.c
void		error_mess(char *mess);
int			error_handling(t_map_data *data);

// init.c
t_map_data	*init_map_data(void);
t_data		*init_data(size_t h, size_t l);
void		init(int *lst, size_t s, int init);

// utils.c
int			max_line(char **maps);
void		add(double n[2], float r[2]);
int			is_digit_str(const char *s);

// minimap.c
void		draw_minmaps(t_map_data *m, t_data *d);
int			move(void *param);
void		draw_player(t_map_data *m, t_data *d, float co[2], int color);

// projection.c
void		draw_projection(t_data *d);

// collision.c
int			collision_wall(double x, double y, t_map_data *m, t_data *d);
int			collision_player(double x, double y, t_map_data *m, t_data *d);

// frame.c
void		my_mlx_pixel_put_c(t_img *img, int x, t_data *d, int color);
void		my_mlx_pixel_put(t_img *img, t_tex *t, int x, t_data *d);
void		apply_frame(t_data *d, t_img *i);

// fill.c
int			fill_info(t_data *d);
void		dest(t_data *d);

// draw_groundsky.c
void		draw_groundsky(t_data *d);

// hooks / input
int			on_keydown(int keycode, t_data *d);
int			on_keyup(int keycode, t_data *d);
int			on_destroy(t_data *d);
void		close_program(t_data *d);
void		handle_movement(t_data *d, double s, double cx, double sx);
void		handle_rotation(t_data *d);

#endif
