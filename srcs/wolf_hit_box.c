/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_hit_box.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:03:19 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 13:03:51 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			player_hit_box(t_wo *wo, float x, float y)
{
	if ((int)(x - 0.1) < 0.1 || (int)(y - 0.1) < 0.1
			|| (int)(x + 0.1) >= wo->m_size.x || (int)(y + 0.1) >= wo->m_size.y)
		return (1);
	if (wo->map[(int)(y)][(int)(x + 0.1)])
		return (1);
	if (wo->map[(int)(y)][(int)(x - 0.1)])
		return (1);
	if (wo->map[(int)(y + 0.1)][(int)(x)])
		return (1);
	if (wo->map[(int)(y - 0.1)][(int)(x)])
		return (1);
	if (wo->map[(int)(y - 0.1)][(int)(x + 0.1)])
		return (1);
	if (wo->map[(int)(y + 0.1)][(int)(x + 0.1)])
		return (1);
	if (wo->map[(int)(y - 0.1)][(int)(x - 0.1)])
		return (1);
	if (wo->map[(int)(y + 0.1)][(int)(x - 0.1)])
		return (1);
	if (wo->map[(int)(y)][(int)(x)])
		return (1);
	return (0);
}
