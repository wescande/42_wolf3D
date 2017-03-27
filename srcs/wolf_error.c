/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 12:01:02 by wescande          #+#    #+#             */
/*   Updated: 2017/02/28 12:01:08 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			error(const char *msg)
{
	if (msg)
		ft_dprintf(2, "{red}%s{eoc}\n", msg);
	exit(1);
}
