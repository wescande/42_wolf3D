/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:31:56 by wescande          #+#    #+#             */
/*   Updated: 2017/02/27 18:18:30 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		get_color(t_wo *wo, int tex_val, int height, t_ivec2 c)
{
	int					color;
	int					pos;

	c.y = (c.y << 8) - (wo->disp.h << 7) + (height << 7);
	if (wo->key[SDL_SCANCODE_LCTRL] && wo->height == 0.0)
		c.y += height << 6;
	c.y = ((c.y * TEXT_HEIGHT) / height) >> 8;
	if (c.y >= TEXT_HEIGHT)
		c.y = TEXT_HEIGHT - 1;
	c.y = TEXT_WIDTH * c.y + c.x;
	if (c.y < 0)
		c.y = 0;
	pos = tex_val - 1;
	color = ((unsigned char *)wo->spr[pos]->pixels)[c.y * 3 + 2] << 16;
	color += ((unsigned char *)wo->spr[pos]->pixels)[c.y * 3 + 1] << 8;
	color += ((unsigned char *)wo->spr[pos]->pixels)[c.y * 3];
	if (color == 0x000000)
		color = 0x123456;
	return (color);
}

void			draw_sprite(t_wo *wo, int tex_val, t_ivec2 p, t_ivec3 coor)
{
	int			pos;
	int			tex_x;

	tex_x = (((coor.x - (p.y - p.x / 2)) << 8) * TEXT_WIDTH / p.x) >> 8;
	pos = coor.y;
	if (wo->key[SDL_SCANCODE_LCTRL] && wo->height == 0.0)
	{
		pos -= (coor.z - coor.y) / 4.0;
		coor.z -= (coor.z - coor.y) / 4.0;
	}
	while (pos < coor.z)
	{
		draw_pix(&wo->disp, coor.x,
				pos + wo->height / wo->sprite_dist,
				get_color(wo, tex_val, p.x, (t_ivec2){tex_x, pos}));
		++pos;
	}
}
