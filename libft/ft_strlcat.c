/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:29:20 by smdyan            #+#    #+#             */
/*   Updated: 2021/11/03 21:36:12 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	offset;
	size_t	res;
	char	*s;

	s = (char *)src;
	len = ft_strlen(s);
	offset = ft_strlen(dst);
	if (size > offset)
		res = offset + len;
	else
		res = len + size;
	i = 0;
	while (i < len && (offset + i + 1) < size)
	{
		*(dst + offset + i) = *(s + i);
		i++;
	}
	if (i != 0)
		*(dst + offset + i) = '\0';
	return (res);
}
