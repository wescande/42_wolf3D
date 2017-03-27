/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 16:54:07 by wescande          #+#    #+#             */
/*   Updated: 2016/12/28 16:55:46 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tablen(char **mytab)
{
	int		i;

	if (!mytab || !*mytab)
		return (0);
	i = 0;
	while (mytab[i])
	{
		++i;
	}
	return (i);
}
