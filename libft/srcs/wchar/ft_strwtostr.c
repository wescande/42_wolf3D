/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwtostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:44:26 by wescande          #+#    #+#             */
/*   Updated: 2016/11/18 13:25:41 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strwtostr(char *dest, const wchar_t *strw)
{
	char	*ret;

	ret = dest;
	while (strw && *strw)
	{
		dest = ft_charwtochar(dest, *strw) + ft_charwlen(*strw);
		++strw;
	}
	*dest = '\0';
	return (ret);
}
