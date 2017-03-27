/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_loadmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 18:11:59 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 12:39:54 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		generate_map(t_wo *wo, t_ld *map)
{
	t_ivec2		i;

	if (!(wo->map = (int **)malloc(sizeof(int *) * (wo->m_size.y + 1))))
		error("malloc error");
	i.y = -1;
	while (++i.y < wo->m_size.y && (i.x = -1))
	{
		if (!(wo->map[i.y] = (int *)malloc(sizeof(int) * wo->m_size.x)))
			error("malloc error");
		while (++i.x < wo->m_size.x)
		{
			if (map && ((t_ivec3 *)map->content)->x == i.x
					&& ((t_ivec3 *)map->content)->y == i.y)
			{
				wo->map[i.y][i.x] = ((t_ivec3 *)map->content)->z;
				map = map->next;
			}
			else
				wo->map[i.y][i.x] = 0;
		}
		while (map && ((t_ivec3 *)map->content)->x != 0
				&& ((t_ivec3 *)map->content)->y <= i.y)
			map = map->next;
	}
	wo->map[i.y] = NULL;
}

static t_ivec3	*set_wall(t_wo *wo, int x, int texture)
{
	t_ivec3		*wall;
	t_sprite	*spr;

	if (!(wall = (t_ivec3 *)malloc(sizeof(t_ivec3))))
		error("malloc error");
	wall->x = x;
	wall->y = wo->m_size.y;
	if (texture < 0)
	{
		wall->z = texture % (NB_SPRITE) - 1;
		if (!(spr = (t_sprite *)malloc(sizeof(t_sprite))))
			error("malloc error");
		spr->pos.x = (float)wall->x + 0.5;
		spr->pos.y = (float)wall->y + 0.5;
		spr->val = -wall->z;
		spr->dst = 0.0;
		ft_ld_pushfront(&wo->l_spr, spr);
	}
	else
		wall->z = texture % (NB_TEXTURE + NB_COLOR);
	return (wall);
}

void			wolf_fill_map(t_wo *wo, t_ld **map, char *line)
{
	char		**li_split;
	int			index;

	li_split = ft_strsplit(line, ' ');
	index = -1;
	while (li_split[++index])
		ft_ld_pushfront(map, set_wall(wo, index, ft_atoi(li_split[index])));
	ft_tabdel(&li_split);
	if (index > wo->m_size.x)
		wo->m_size.x = index;
}

static int		get_player_pos(t_wo *wo)
{
	t_ivec2		i;

	i.y = wo->m_size.y / 2;
	while (++i.y < wo->m_size.y && (i.x = wo->m_size.x / 2))
	{
		while (++i.x < wo->m_size.x)
			if (!wo->map[i.y][i.x])
			{
				wo->cam.pos.x = i.x + 0.5;
				wo->cam.pos.y = i.y + 0.5;
				return (0);
			}
	}
	i.y = wo->m_size.y / 2;
	while (--i.y && (i.x = wo->m_size.x / 2))
	{
		while (--i.x)
			if (!wo->map[i.y][i.x])
			{
				wo->cam.pos.x = i.x + 0.5;
				wo->cam.pos.y = i.y + 0.5;
				return (0);
			}
	}
	return (1);
}

int				wolf_loadmap(t_wo *wo, int argc, char **argv)
{
	int		fd;
	char	*line;
	t_ld	*map;

	if (argc != 2)
		error("wolf3D: Inccorrect nb of argument");
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		perror(argv[1]);
		return (1);
	}
	map = NULL;
	wo->m_size = (t_ivec2){0, 0};
	while (get_next_line(fd, &line) > 0)
	{
		wolf_fill_map(wo, &map, line);
		ft_strdel(&line);
		++wo->m_size.y;
	}
	ft_strdel(&line);
	ft_ld_reverse(&map);
	generate_map(wo, map);
	ft_ld_clear(&map, &ft_memdel);
	close(fd);
	return (get_player_pos(wo));
}
