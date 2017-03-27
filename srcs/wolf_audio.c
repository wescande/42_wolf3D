/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_audio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 08:53:53 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 13:07:50 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	audiocallback(void *udata, Uint8 *stream, int len)
{
	t_audio	*audio;

	audio = (t_audio *)udata;
	if (audio->audiolen == 0)
		return ;
	memset(stream, 0, len);
	if (audio->audiopos < audio->audiolen)
	{
		if (audio->audiopos + len > audio->audiolen)
			len = audio->audiolen - audio->audiopos;
		SDL_MixAudio(stream, audio->audiobuffer + audio->audiopos,
				len, SDL_MIX_MAXVOLUME);
		audio->audiopos += len;
	}
	audio->audiolen -= len;
}

int		audio_init(t_audio *audio)
{
	audio->audiospec.freq = 44100;
	audio->audiospec.format = AUDIO_S16;
	audio->audiospec.channels = 2;
	audio->audiospec.samples = 1024;
	audio->audiospec.callback = audiocallback;
	audio->audiospec.userdata = audio;
	if (SDL_OpenAudio(&audio->audiospec, NULL) < 0)
	{
		ft_dprintf(2, "Erreur d'ouverture audio\n");
		return (-1);
	}
	return (0);
}

int		wolf_audio(t_audio *audio)
{
	if (audio_init(audio))
		return (1);
	if (!SDL_LoadWAV(SOUND_1, &audio->audiospec,
				&audio->audiobuffer, &audio->audiobufferlen))
	{
		ft_dprintf(2, "Erreur lors du chargement du fichier WAV.\n");
		return (1);
	}
	return (0);
}
