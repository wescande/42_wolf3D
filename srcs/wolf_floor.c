/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 11:16:47 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 12:39:36 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		get_color(t_wo *wo, t_ivec2 pos)
{
	int					color;
	int					y;

	y = TEXT_WIDTH * pos.y + pos.x;
	color = ((unsigned char *)wo->tex[0]->pixels)[y * 3 + 2] * 256 * 256;
	color += ((unsigned char *)wo->tex[0]->pixels)[y * 3 + 1] * 256;
	color += ((unsigned char *)wo->tex[0]->pixels)[y * 3];
	return ((color >> 1) & 8355711);
}

static void		init_floor(t_colonne *col, t_vec2 *floor)
{
	if ((!col->side && col->ray.dir.x > 0))
	{
		floor->x = col->hit.x;
		floor->y = col->hit.y + col->wall;
	}
	else if ((!col->side && col->ray.dir.x < 0))
	{
		floor->x = col->hit.x + 1.0;
		floor->y = col->hit.y + col->wall;
	}
	else if ((col->side && col->ray.dir.y > 0))
	{
		floor->x = col->hit.x + col->wall;
		floor->y = col->hit.y;
	}
	else
	{
		floor->x = col->hit.x + col->wall;
		floor->y = col->hit.y + 1.0;
	}
}

t_ivec2			get_tex_position(t_wo *wo, float dist, t_vec2 *floor)
{
	t_ivec2	tex;
	t_vec2	cur_floor;
	float	ratio;

	ratio = (wo->key[SDL_SCANCODE_LCTRL] && wo->height == 0.0 ? 2.0 : 1.0);
	ratio = ratio * wo->disp.ratio - dist;
	cur_floor.x = (dist * floor->x + ratio * wo->cam.pos.x);
	cur_floor.y = (dist * floor->y + ratio * wo->cam.pos.y);
	if (wo->key[SDL_SCANCODE_LCTRL] && wo->height == 0.0)
	{
		tex.x = (int)(cur_floor.x * TEXT_WIDTH / 2) % TEXT_WIDTH;
		tex.y = (int)(cur_floor.y * TEXT_HEIGHT / 2) % TEXT_HEIGHT;
	}
	else
	{
		tex.x = (int)(cur_floor.x * TEXT_WIDTH) % TEXT_WIDTH;
		tex.y = (int)(cur_floor.y * TEXT_HEIGHT) % TEXT_HEIGHT;
	}
	if (tex.x < 0)
		tex.x = -tex.x;
	if (tex.y < 0)
		tex.y = -tex.y;
	return (tex);
}

void			wolf_floor(t_wo *wo, int x, t_colonne *col, int pos)
{
	t_vec2	floor;
	t_ivec2	tex;
	float	dist;

	init_floor(col, &floor);
	while (pos < wo->disp.h)
	{
		dist = ((float)wo->disp.h
				/ (float)(2 * (pos - col->decal) - wo->disp.h)) / col->distance;
		tex = get_tex_position(wo, dist, &floor);
		draw_pix(&wo->disp, x, pos, get_color(wo, tex));
		++pos;
	}
}
