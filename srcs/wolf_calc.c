/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_calc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:31:33 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 12:05:11 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		set_step(t_colonne *col, t_dst *dst)
{
	if (col->ray.dir.x < 0)
	{
		col->step.x = -1;
		dst->side.x = (col->ray.pos.x - col->hit.x) * dst->dta.x;
	}
	else
	{
		col->step.x = 1;
		dst->side.x = (col->hit.x + 1.0 - col->ray.pos.x) * dst->dta.x;
	}
	if (col->ray.dir.y < 0)
	{
		col->step.y = -1;
		dst->side.y = (col->ray.pos.y - col->hit.y) * dst->dta.y;
	}
	else
	{
		col->step.y = 1;
		dst->side.y = (col->hit.y + 1.0 - col->ray.pos.y) * dst->dta.y;
	}
}

static float	distance_calc(t_colonne *col)
{
	if (col->side)
		return (((float)col->hit.y - col->ray.pos.y
					+ (float)(1 - col->step.y) / 2.0) / col->ray.dir.y);
	else
		return (((float)col->hit.x - col->ray.pos.x
					+ (float)(1 - col->step.x) / 2.0) / col->ray.dir.x);
}

static float	catch_hit(t_wo *wo, t_colonne *col)
{
	t_dst		dst;

	col->hit.x = (int)col->ray.pos.x;
	col->hit.y = (int)col->ray.pos.y;
	dst.dta.x = sqrt(1 + (col->ray.dir.y * col->ray.dir.y)
			/ (col->ray.dir.x * col->ray.dir.x));
	dst.dta.y = sqrt(1 + (col->ray.dir.x * col->ray.dir.x)
			/ (col->ray.dir.y * col->ray.dir.y));
	set_step(col, &dst);
	while (1)
	{
		if (col->hit.y >= wo->m_size.y || col->hit.x >= wo->m_size.x
				|| col->hit.y <= 0 || col->hit.x <= 0
				|| wo->map[col->hit.y][col->hit.x] > 0)
			return (distance_calc(col));
		col->side = ray_hit(&dst, &col->hit, &col->step);
	}
}

static int		get_hit_value(t_wo *wo, t_hit *hit)
{
	if (hit->x < 0 || hit->y < 0
			|| hit->y >= wo->m_size.y || hit->x >= wo->m_size.x)
		return (0);
	if (wo->map[hit->y][hit->x] < 0)
		return (0);
	return (wo->map[hit->y][hit->x]);
}

void			wolf_calc(t_wo *wo, int x, t_colonne *col)
{
	ray_init(wo, &col->ray, x);
	col->distance = catch_hit(wo, col);
	col->height = (int)(((float)wo->disp.h / col->distance) / wo->disp.ratio);
	col->decal = (int)(wo->height / col->distance);
	col->start = -col->height / 2 + wo->disp.h / 2 + col->decal;
	if (wo->key[SDL_SCANCODE_LCTRL] && wo->height == 0.0)
		col->start -= col->height / 4.0;
	col->end = col->start + col->height;
	col->start *= !(col->start < 0);
	col->end = (col->end >= wo->disp.h) ? wo->disp.h : col->end;
	col->hit_value = get_hit_value(wo, &col->hit);
	if (col->side)
		col->wall = col->ray.pos.x + col->distance * col->ray.dir.x;
	else
		col->wall = col->ray.pos.y + col->distance * col->ray.dir.y;
	col->wall -= floor(col->wall);
	col->tex = col->wall * (float)(TEXT_WIDTH);
	if ((col->side && col->ray.dir.y < 0) || (!col->side && col->ray.dir.x > 0))
		col->tex = TEXT_WIDTH - col->tex - 1;
	wo->z_buffer[x] = col->distance;
}
