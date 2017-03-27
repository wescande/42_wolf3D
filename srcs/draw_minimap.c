/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:03:02 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 13:03:50 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				get_simple_color(int hit)
{
	if (hit == 1)
		return (0xFF0000);
	else if (hit == 2)
		return (0x00FF00);
	else if (hit == 3)
		return (0x0000FF);
	else if (hit == 4)
		return (0xFFFFFF);
	else if (hit == 5)
		return (0x010101);
	else if (hit > 0)
		return (0x707070);
	else if (hit < 0)
		return (0xFFFF00);
	return (0x123456);
}

static int		get_color_minimap(t_wo *wo, t_ivec2 pos)
{
	int		color;

	if (pos.x < 0 || pos.y < 0
			|| pos.y >= wo->m_size.y || pos.x >= wo->m_size.x)
		return (0);
	color = get_simple_color(wo->map[pos.y][pos.x]);
	return (color);
}

static void		draw_square(t_wo *wo, t_ivec2 pos, t_ivec2 size, int color)
{
	t_ivec2		i;

	i.y = -1;
	while (++i.y < size.y && (i.x = -1))
		while (++i.x < size.x)
			draw_pix(&wo->disp, pos.x + i.x, pos.y + i.y, color);
}

void			draw_minimap(t_wo *wo)
{
	t_ivec2		i;

	i.y = -1;
	while (++i.y < wo->m_size.y && (i.x = -1))
		while (++i.x < wo->m_size.x)
			draw_square(wo, (t_ivec2){i.y * 4, i.x * 4},
					(t_ivec2){4, 4}, get_color_minimap(wo, i));
	draw_square(wo,
			(t_ivec2){wo->cam.pos.y * 4.0 - 1.5, wo->cam.pos.x * 4.0 - 1.5},
			(t_ivec2){4, 4}, 0xFF00FF);
}
