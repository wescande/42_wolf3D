/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 11:38:23 by wescande          #+#    #+#             */
/*   Updated: 2017/02/21 15:29:02 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		draw_texture(t_wo *wo, int x, int x_text)
{
	int		color;
	int		pos;
	int		pos_text;

	pos = -1;
	while (++pos < wo->disp.h)
	{
		pos_text = pos << 8;
		pos_text = ((pos_text * SKY_HEIGHT) / wo->disp.h) >> 8;
		if (pos_text >= SKY_HEIGHT)
			pos_text = SKY_HEIGHT - 1;
		if (pos_text < 0)
			pos_text = 0;
		pos_text = SKY_WIDTH * pos_text + x_text;
		color = ((unsigned char *)wo->skybox->pixels)[pos_text * 3 + 2] << 16;
		color += ((unsigned char *)wo->skybox->pixels)[pos_text * 3 + 1] << 8;
		color += ((unsigned char *)wo->skybox->pixels)[pos_text * 3];
		draw_pix(&wo->disp, x, pos, color);
	}
}

static void		draw_vertical_line(t_wo *wo, int x)
{
	t_ray		look;
	float		sky_x;
	float		cam_x;

	cam_x = (2.0 * (float)x / (float)wo->disp.w - 1.0)
		* wo->disp.ratio * wo->disp.ratio;
	look.dir.x = wo->cam.dir.x + wo->cam.plane.x * cam_x;
	look.dir.y = wo->cam.dir.y + wo->cam.plane.y * cam_x;
	cam_x = M_PI / 2 + atan((look.dir.y / look.dir.x));
	if (look.dir.x < 0.0)
		cam_x += M_PI;
	sky_x = (cam_x / (2.0 * M_PI)) * (float)SKY_WIDTH;
	draw_texture(wo, x, (int)sky_x);
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

void			draw_skybox(t_wo *wo)
{
	int			x;
	int			step;
	t_thread	thread[NB_THREAD];

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
}
