/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wolf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 20:04:44 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 12:54:16 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		wolf_init(t_wo *wo)
{
	int		fuck_la_norminette;

	fuck_la_norminette = NB_KEY * 4;
	wo->cam.pos.x = -1;
	wo->cam.pos.y = -1;
	wo->cam.dir.x = -1;
	wo->cam.dir.y = 0;
	wo->cam.plane.x = 0.0;
	wo->cam.plane.y = 0.66;
	wo->height = 0.0;
	wo->acc = 0.0;
	ft_bzero(wo->key, fuck_la_norminette);
	wo->disp.framebuffer = NULL;
	wo->disp.px = NULL;
	wo->z_buffer = NULL;
	return (0);
}

static int		wolf_exit(t_wo *wo)
{
	int i;

	i = -1;
	ft_tabdel((char ***)&wo->map);
	ft_memdel((void **)&wo->disp.px);
	ft_ld_clear(&wo->l_spr, &ft_memdel);
	ft_memdel((void **)&wo->z_buffer);
	while (++i < NB_TEXTURE)
		SDL_FreeSurface(wo->tex[i]);
	SDL_FreeSurface(wo->skybox);
	SDL_DestroyTexture(wo->disp.framebuffer);
	SDL_DestroyRenderer(wo->disp.renderer);
	SDL_DestroyWindow(wo->disp.win);
	SDL_FreeWAV(wo->audio.audiobuffer);
	SDL_CloseAudio();
	SDL_Quit();
	return (0);
}

static void		wolf_loop(t_wo *wo)
{
	float			frametime;
	int				ret;

	wo->time = SDL_GetTicks();
	draw_screen(wo);
	while (1)
	{
		wo->oldtime = wo->time;
		if (display_update(&wo->disp))
			error("SDL display error");
		wo->time = SDL_GetTicks();
		frametime = (wo->time - wo->oldtime) / 1000.0;
		if (wo->height == 0.0)
			wo->move = frametime * 3.5
				/ ((float)wo->key[SDL_SCANCODE_LCTRL] + 1.0)
				* ((float)wo->key[SDL_SCANCODE_LSHIFT] / 1.5 + 1.0);
		else
			wo->move = frametime * 3.5;
		wo->rot = frametime * 1.7;
		if ((ret = input_update(wo)) == -1)
			break ;
		ret += move(wo) + rot(wo) + jump(wo);
		if (ret)
			draw_screen(wo);
	}
}

static int		wolf_loadtexture(t_wo *wo)
{
	if (!(wo->tex[0] = SDL_LoadBMP(TEXT_1)))
		return (1);
	if (!(wo->tex[1] = SDL_LoadBMP(TEXT_2)))
		return (2);
	if (!(wo->tex[2] = SDL_LoadBMP(TEXT_3)))
		return (3);
	if (!(wo->tex[3] = SDL_LoadBMP(TEXT_4)))
		return (4);
	if (!(wo->tex[4] = SDL_LoadBMP(TEXT_5)))
		return (5);
	if (!(wo->tex[5] = SDL_LoadBMP(TEXT_6)))
		return (6);
	if (!(wo->tex[6] = SDL_LoadBMP(TEXT_7)))
		return (7);
	if (!(wo->tex[7] = SDL_LoadBMP(TEXT_8)))
		return (8);
	if (!(wo->spr[0] = SDL_LoadBMP(SPRIT_1)))
		return (8);
	if (!(wo->spr[1] = SDL_LoadBMP(SPRIT_2)))
		return (8);
	if (!(wo->skybox = SDL_LoadBMP(TEXT_SKY)))
		return (8);
	return (0);
}

int				main(int argc, char **argv)
{
	t_wo			wo;

	if (wolf_init(&wo))
		error("initialisation error");
	if (wolf_loadmap(&wo, argc, argv))
		error("map input error");
	if (wolf_loadtexture(&wo))
		error("loading texture end with error");
	if (create_win(&wo, "Wolf 3D", 1600, 1200))
		error("SDL error");
	if (wolf_audio(&wo.audio))
		error("Audio error");
	wo.audio.audiolen = 5000;
	wo.audio.play = 0;
	wolf_loop(&wo);
	return (wolf_exit(&wo));
}
