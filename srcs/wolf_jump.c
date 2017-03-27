/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_jump.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 12:13:58 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 12:37:57 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int	manage_jump(t_wo *wo)
{
	if (wo->acc || wo->height)
	{
		wo->height += wo->acc / wo->move;
		wo->acc -= 3.0 * wo->move;
		if (wo->height < 0.0)
		{
			wo->height = 0.0;
			wo->acc = 0.0;
		}
		return (1);
	}
	return (0);
}

int			jump(t_wo *wo)
{
	int			ret;
	static int	press = 0;

	if (wo->key[SDL_SCANCODE_SPACE] && !wo->key[SDL_SCANCODE_LCTRL] && !press)
		press = 1;
	else if (!(wo->key[SDL_SCANCODE_SPACE])
			&& !wo->key[SDL_SCANCODE_LCTRL] && press)
	{
		press = 0;
		if (wo->height == 0.0)
			wo->acc = 4.5;
	}
	ret = manage_jump(wo);
	return (ret);
}
