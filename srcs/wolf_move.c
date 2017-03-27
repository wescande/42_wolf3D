/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:03:29 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 13:03:53 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	deplace(t_wo *wo, float x, float y)
{
	if (!player_hit_box(wo, x, wo->cam.pos.y))
		wo->cam.pos.x = x;
	if (!player_hit_box(wo, wo->cam.pos.x, y))
		wo->cam.pos.y = y;
	return (1);
}

int			lateral_move(t_wo *wo, int ret)
{
	if (wo->key[SDL_SCANCODE_Q] && !wo->key[SDL_SCANCODE_E])
	{
		if (ret)
			ret += deplace(wo, wo->cam.pos.x - wo->move / 1.5 * wo->cam.dir.y,
					wo->cam.pos.y + wo->move / 1.5 * wo->cam.dir.x);
		else
			ret += deplace(wo, wo->cam.pos.x - wo->move * wo->cam.dir.y,
					wo->cam.pos.y + wo->move * wo->cam.dir.x);
	}
	else if (wo->key[SDL_SCANCODE_E] && !wo->key[SDL_SCANCODE_Q])
	{
		if (ret)
			ret += deplace(wo, wo->cam.pos.x + wo->move / 1.5 * wo->cam.dir.y,
					wo->cam.pos.y - wo->move / 1.5 * wo->cam.dir.x);
		else
			ret += deplace(wo, wo->cam.pos.x + wo->move * wo->cam.dir.y,
					wo->cam.pos.y - wo->move * wo->cam.dir.x);
	}
	return (ret);
}

int			move(t_wo *wo)
{
	int		ret;

	ret = 0;
	if ((wo->key[SDL_SCANCODE_W] || wo->key[SDL_SCANCODE_UP])
			&& !(wo->key[SDL_SCANCODE_S] || wo->key[SDL_SCANCODE_DOWN]))
	{
		if (wo->key[SDL_SCANCODE_Q] || wo->key[SDL_SCANCODE_E])
			ret += deplace(wo, wo->cam.pos.x + wo->move / 1.5 * wo->cam.dir.x,
					wo->cam.pos.y + wo->move / 1.5 * wo->cam.dir.y);
		else
			ret += deplace(wo, wo->cam.pos.x + wo->move * wo->cam.dir.x,
					wo->cam.pos.y + wo->move * wo->cam.dir.y);
	}
	else if ((wo->key[SDL_SCANCODE_DOWN] || wo->key[SDL_SCANCODE_S])
			&& !(wo->key[SDL_SCANCODE_W] || wo->key[SDL_SCANCODE_UP]))
	{
		if (wo->key[SDL_SCANCODE_Q] || wo->key[SDL_SCANCODE_E])
			ret += deplace(wo, wo->cam.pos.x - wo->move / 1.5 * wo->cam.dir.x,
					wo->cam.pos.y - wo->move / 1.5 * wo->cam.dir.y);
		else
			ret += deplace(wo, wo->cam.pos.x - wo->move * wo->cam.dir.x,
					wo->cam.pos.y - wo->move * wo->cam.dir.y);
	}
	ret = lateral_move(wo, ret);
	return (ret);
}

static int	set_rotation(t_wo *wo, float rot)
{
	float	tmp;

	tmp = wo->cam.dir.x;
	wo->cam.dir.x = wo->cam.dir.x * cos(rot)
		- wo->cam.dir.y * sin(rot);
	wo->cam.dir.y = tmp * sin(rot) + wo->cam.dir.y * cos(rot);
	tmp = wo->cam.plane.x;
	wo->cam.plane.x = wo->cam.plane.x * cos(rot)
		- wo->cam.plane.y * sin(rot);
	wo->cam.plane.y = tmp * sin(rot) + wo->cam.plane.y * cos(rot);
	return (1);
}

int			rot(t_wo *wo)
{
	int ret;

	ret = 0;
	if ((wo->key[SDL_SCANCODE_D] || wo->key[SDL_SCANCODE_RIGHT])
			&& !(wo->key[SDL_SCANCODE_A] || wo->key[SDL_SCANCODE_LEFT]))
		ret += set_rotation(wo, -wo->rot);
	else if ((wo->key[SDL_SCANCODE_A] || wo->key[SDL_SCANCODE_LEFT])
			&& !(wo->key[SDL_SCANCODE_D] || wo->key[SDL_SCANCODE_RIGHT]))
		ret += set_rotation(wo, wo->rot);
	return (ret);
}
