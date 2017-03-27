/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:03:23 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 13:03:52 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		manage_key(t_wo *wo)
{
	static int		press = 0;

	if (!press && wo->key[SDL_SCANCODE_M])
		press = 1;
	else if (press == 1 && !wo->key[SDL_SCANCODE_M])
	{
		press = 0;
		wo->audio.play = !wo->audio.play;
		SDL_PauseAudio(!wo->audio.play);
	}
}

int				input_update(t_wo *wo)
{
	SDL_Event	event;
	int			ret;

	ret = 0;
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
			return (-1);
		else if (event.type == SDL_WINDOWEVENT
				&& event.window.event == SDL_WINDOWEVENT_RESIZED)
			ret += set_sdl_size(wo, event.window.data1, event.window.data2);
		else if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				return (-1);
			if (event.key.keysym.scancode < NB_KEY && ++ret)
				wo->key[event.key.keysym.scancode] = 1;
		}
		else if (event.type == SDL_KEYUP)
			if (event.key.keysym.scancode < NB_KEY && ++ret)
				wo->key[event.key.keysym.scancode] = 0;
	}
	manage_key(wo);
	return (ret);
}
