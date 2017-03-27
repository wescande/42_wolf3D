/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 19:28:16 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 12:07:15 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <math.h>
# include <pthread.h>
# include <libft.h>
# include <SDL.h>

# define NB_THREAD 9
# define NB_KEY 300
# define NB_TEXTURE 8
# define NB_SPRITE 2
# define NB_COLOR 6
# define TEXT_SKY "pics/skybox.bmp"
# define TEXT_1 "pics/wood.bmp"
# define TEXT_2 "pics/bluestone.bmp"
# define TEXT_3 "pics/eagle.bmp"
# define TEXT_4 "pics/greystone.bmp"
# define TEXT_5 "pics/mossy.bmp"
# define TEXT_6 "pics/purplestone.bmp"
# define TEXT_7 "pics/redbrick.bmp"
# define TEXT_8 "pics/colorstone.bmp"
# define SPRIT_1 "pics/pillar.bmp"
# define SPRIT_2 "pics/barrel.bmp"
# define SOUND_1 "sound/01_-_Wolfenstein_3D_-_DOS_-_Horst-Wessel-Lied.wav"
# define TEXT_WIDTH 64
# define TEXT_HEIGHT 64
# define SKY_HEIGHT 1024
# define SKY_WIDTH 2048

typedef struct	s_ivec3
{
	int			x;
	int			y;
	int			z;
}				t_ivec3;

typedef struct	s_ivec2
{
	int			x;
	int			y;
}				t_ivec2;

typedef struct	s_vec2
{
	float		x;
	float		y;
}				t_vec2;

typedef struct	s_hit
{
	int			x;
	int			y;
	float		dist;
}				t_hit;

typedef struct	s_dist
{
	t_vec2		side;
	t_vec2		dta;
}				t_dst;

typedef struct	s_ray
{
	t_vec2		pos;
	t_vec2		dir;
}				t_ray;

typedef struct	s_sprite
{
	t_vec2		pos;
	int			val;
	float		dst;
}				t_sprite;

typedef struct	s_camera
{
	t_vec2		pos;
	t_vec2		dir;
	t_vec2		plane;
}				t_camera;

typedef struct	s_colonne
{
	int			tex;
	int			hit_value;
	int			start;
	int			decal;
	int			height;
	int			end;
	int			side;
	float		distance;
	float		wall;
	t_ray		ray;
	t_hit		hit;
	t_ivec2		step;
	t_dst		dst;
}				t_colonne;

typedef struct	s_display
{
	SDL_Window			*win;
	SDL_Renderer		*renderer;
	SDL_Texture			*framebuffer;
	const char			*title;
	int					w;
	int					h;
	float				ratio;
	char				*px;
}				t_display;

typedef struct	s_audio
{
	SDL_AudioSpec		audiospec;
	Uint8				*audiobuffer;
	Uint32				audiobufferlen;
	Uint32				audiolen;
	Uint32				audiopos;
	int					play;
}				t_audio;

typedef struct	s_wo
{
	t_display			disp;
	t_audio				audio;
	t_camera			cam;
	SDL_Surface			*tex[NB_TEXTURE];
	SDL_Surface			*spr[NB_SPRITE];
	SDL_Surface			*skybox;
	int					**map;
	t_ivec2				m_size;
	int					key[NB_KEY];
	unsigned int		time;
	unsigned int		oldtime;
	float				move;
	float				rot;
	float				height;
	float				acc;
	float				*z_buffer;
	float				sprite_dist;
	t_ld				*l_spr;
}				t_wo;

typedef struct	s_thread
{
	pthread_t	id;
	t_wo		*wo;
	int			x;
	int			width;
}				t_thread;

/*
** Draw
*/
void			draw_screen(t_wo *wo);
void			draw_skybox(t_wo *wo);
void			draw_sprite(t_wo *wo, int tex_val, t_ivec2 p, t_ivec3 coor);
void			draw_minimap(t_wo *wo);
void			draw_pix(t_display *disp, int x, int y, int color);
int				display_update(t_display *disp);
int				get_simple_color(int hit);
/*
** Input
*/
int				input_update(t_wo *wo);
int				set_sdl_size(t_wo *wo, int width, int height);
int				create_win(t_wo *wo, const char *title, int width, int height);
int				move(t_wo *wo);
int				jump(t_wo *wo);
int				rot(t_wo *wo);
int				wolf_loadmap(t_wo *wo, int argc, char **argv);
int				wolf_audio(t_audio *audio);
/*
** Output
*/
void			error(const char *msg);
/*
** Calc
*/
void			wolf_calc(t_wo *wo, int x, t_colonne *col);
void			wolf_sprite(t_wo *wo);
void			wolf_floor(t_wo *wo, int x, t_colonne *col, int pos);
void			ray_init(t_wo *wo, t_ray *ray, int x);
int				ray_hit(t_dst *dst, t_hit *hit, t_ivec2 *step);
int				player_hit_box(t_wo *wo, float x, float y);

#endif
