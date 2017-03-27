/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:03:34 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 13:03:54 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			ray_init(t_wo *wo, t_ray *ray, int x)
{
	float	cam_x;

	cam_x = (2.0 * (float)x / (float)wo->disp.w - 1.0)
		* wo->disp.ratio * wo->disp.ratio;
	ray->pos.x = wo->cam.pos.x;
	ray->pos.y = wo->cam.pos.y;
	ray->dir.x = wo->cam.dir.x + wo->cam.plane.x * cam_x;
	ray->dir.y = wo->cam.dir.y + wo->cam.plane.y * cam_x;
}

int				ray_hit(t_dst *dst, t_hit *hit, t_ivec2 *step)
{
	if (dst->side.x < dst->side.y)
	{
		dst->side.x += dst->dta.x;
		hit->x += step->x;
		return (0);
	}
	else
	{
		dst->side.y += dst->dta.y;
		hit->y += step->y;
		return (1);
	}
}
