/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:03:39 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 13:08:41 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int				set_sdl_size(t_wo *wo, int width, int height)
{
	wo->disp.w = width;
	wo->disp.h = height;
	wo->disp.ratio = (float)width / (float)height * 0.75;
	if (wo->disp.framebuffer)
		SDL_DestroyTexture(wo->disp.framebuffer);
	if (!(wo->disp.framebuffer = SDL_CreateTexture(wo->disp.renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC,
			wo->disp.w, wo->disp.h)))
		return (0);
	if (wo->disp.px)
		ft_memdel((void **)&wo->disp.px);
	if (!(wo->disp.px = (char *)ft_memalloc(sizeof(int)
					* wo->disp.w * wo->disp.h)))
		error("malloc error");
	if (!(wo->z_buffer))
		ft_memdel((void **)&wo->z_buffer);
	if (!(wo->z_buffer = (float *)malloc(sizeof(float) * wo->disp.w)))
		error("malloc error");
	return (1);
}

int				create_win(t_wo *wo, const char *title, int width, int height)
{
	wo->disp.title = title;
	wo->disp.w = width;
	wo->disp.h = height;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		return (1);
	if (!(wo->disp.win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, width, height,
					SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)))
		return (1);
	if (!(wo->disp.renderer = SDL_CreateRenderer(wo->disp.win, -1, 0)))
		return (1);
	return (!set_sdl_size(wo, width, height));
}

int				display_update(t_display *disp)
{
	if (SDL_UpdateTexture(disp->framebuffer,
				NULL, disp->px, disp->w * sizeof(int)))
		return (ft_dprintf(2, "SDL_UpdateTexture failed\n"));
	if (SDL_RenderCopy(disp->renderer, disp->framebuffer, NULL, NULL))
		return (ft_dprintf(2, "SDL_RenderCopy failed\n"));
	SDL_RenderPresent(disp->renderer);
	if (SDL_RenderClear(disp->renderer))
		return (ft_dprintf(2, "SDL_RenderClear failed\n"));
	return (0);
}
