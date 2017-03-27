/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 15:29:49 by wescande          #+#    #+#             */
/*   Updated: 2017/02/27 18:18:44 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			draw_pix(t_display *disp, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= disp->w || y >= disp->h || color == 0x123456)
		return ;
	((int *)disp->px)[(x + y * disp->w)] = color;
}

static int		get_color(t_wo *wo, t_colonne *col, int y)
{
	int					color;
	int					pos;

	if (col->hit_value < NB_COLOR)
		color = get_simple_color(col->hit_value);
	else
	{
		y = (y << 8) - (wo->disp.h << 7) + (col->height << 7);
		if (wo->key[SDL_SCANCODE_LCTRL] && wo->height == 0.0)
			y += col->height << 6;
		y = ((y * TEXT_HEIGHT) / col->height) >> 8;
		if (y >= TEXT_HEIGHT)
			y = TEXT_HEIGHT - 1;
		y = TEXT_WIDTH * y + col->tex;
		if (y < 0)
			y = 0;
		pos = col->hit_value - NB_COLOR;
		color = ((unsigned char *)wo->tex[pos]->pixels)[y * 3 + 2] << 16;
		color += ((unsigned char *)wo->tex[pos]->pixels)[y * 3 + 1] << 8;
		color += ((unsigned char *)wo->tex[pos]->pixels)[y * 3];
	}
	if (col->side && color != 0x123456)
		return ((color >> 1) & 8355711);
	return (color);
}

static void		draw_vertical_line(t_wo *wo, int x)
{
	t_colonne	col;
	int			pos;

	if (x >= wo->disp.w)
		return ;
	wolf_calc(wo, x, &col);
	pos = col.start;
	while (pos < col.end)
	{
		draw_pix(&wo->disp, x, pos,
				get_color(wo, &col, pos - (wo->height / col.distance)));
		++pos;
	}
	wolf_floor(wo, x, &col, pos);
}

static void		*draw_block(void *data)
{
	int			x;
	t_thread	*thread;

	thread = (t_thread *)data;
	x = -1;
	while (++x < thread->width)
		draw_vertical_line(thread->wo, x + thread->x);
	return (0);
}

void			draw_screen(t_wo *wo)
{
	int			x;
	int			step;
	t_thread	thread[NB_THREAD];

	draw_skybox(wo);
	x = -1;
	step = wo->disp.w / NB_THREAD + 1;
	while (++x < NB_THREAD)
	{
		thread[x].x = x * step;
		thread[x].width = step;
		thread[x].wo = wo;
		pthread_create(&thread[x].id, NULL, &draw_block, thread + x);
	}
	x = -1;
	while (++x < NB_THREAD)
		pthread_join(thread[x].id, NULL);
	if (wo->l_spr)
		wolf_sprite(wo);
	draw_minimap(wo);
}
