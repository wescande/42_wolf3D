/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wescande <wescande@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 21:29:24 by wescande          #+#    #+#             */
/*   Updated: 2016/12/02 17:26:36 by wescande         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
{
	int		len;
	int		start;
	int		end;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	start = 0;
	while (s[start] && ft_isspa(s[start]))
		++start;
	if (start == len)
		return (ft_strnew(0));
	end = 0;
	while (ft_isspa(s[len - end - 1]) && len - end - 1 > 0)
		++end;
	return (ft_strsub(s, start, len - end - start));
}
