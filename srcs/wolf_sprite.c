/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 13:29:13 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 12:48:28 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		order_list(t_wo *wo)
{
	t_ld		*cur;
	t_sprite	*spr;
	int			sorting;

	cur = wo->l_spr;
	while (cur)
	{
		spr = ((t_sprite *)cur->content);
		spr->dst = powf(wo->cam.pos.x - spr->pos.x, 2)
			+ powf(wo->cam.pos.y - spr->pos.y, 2);
		cur = cur->next;
	}
	sorting = 1;
	while (sorting-- && (cur = ft_ld_front(wo->l_spr)))
		while (cur->next)
		{
			if (((t_sprite *)cur->content)->dst <
					((t_sprite *)cur->next->content)->dst)
			{
				cur = ft_ld_swap(cur);
				sorting = 1;
			}
			cur = cur->next;
		}
	wo->l_spr = ft_ld_front(wo->l_spr);
}

static void		sprite_again(t_wo *wo, int tex_val, float tr_y, int x_screen)
{
	int		height;
	int		x;
	t_ivec2	s_draw;
	t_ivec2	e_draw;

	height = (int)((float)wo->disp.h / tr_y);
	if (height < 0)
		height = -height;
	s_draw.y = (wo->disp.h - height) / 2;
	e_draw.y = s_draw.y + height;
	s_draw.y *= !(s_draw.y < 0);
	e_draw.y = (e_draw.y >= wo->disp.h) ? wo->disp.h : e_draw.y;
	s_draw.x = x_screen - height / 2;
	e_draw.x = s_draw.x + height;
	s_draw.x *= !(s_draw.x < 0);
	e_draw.x = (e_draw.x >= wo->disp.w) ? wo->disp.w : e_draw.x;
	x = s_draw.x;
	while (x < e_draw.x)
	{
		if (tr_y < wo->z_buffer[x])
			draw_sprite(wo, tex_val,
					(t_ivec2){height, x_screen},
					(t_ivec3){x, s_draw.y, e_draw.y});
		++x;
	}
}

void			wolf_sprite(t_wo *wo)
{
	t_ld		*cur;
	t_vec2		sprite;
	float		inve;
	float		tmp;
	int			x_screen;

	order_list(wo);
	cur = wo->l_spr;
	while (cur)
	{
		sprite.x = ((t_sprite *)cur->content)->pos.x - wo->cam.pos.x;
		sprite.y = ((t_sprite *)cur->content)->pos.y - wo->cam.pos.y;
		inve = 1.0 /
			(wo->cam.plane.x * wo->cam.dir.y - wo->cam.plane.y * wo->cam.dir.x);
		tmp = sprite.x;
		sprite.x = inve * (wo->cam.dir.y * tmp - wo->cam.dir.x * sprite.y);
		sprite.y = inve * (-wo->cam.plane.y * tmp + wo->cam.plane.x * sprite.y);
		x_screen = (int)((float)wo->disp.w / 2.0 * (1.0 + sprite.x / sprite.y));
		wo->sprite_dist = sprite.y;
		if (sprite.y > 0.0)
			sprite_again(wo, ((t_sprite *)cur->content)->val,
					sprite.y, x_screen);
		cur = cur->next;
	}
}
