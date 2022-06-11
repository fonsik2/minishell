/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:23:58 by smdyan            #+#    #+#             */
/*   Updated: 2021/10/23 16:58:22 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	dst2 = (unsigned char *)dst;
	src2 = (unsigned char *)src;
	if (dst2 > src2)
	{
		i = len;
		while (i > 0)
		{
			*(dst2 + (i - 1)) = *(src2 + (i - 1));
			i--;
		}
	}
	else if (dst2 < src2)
	{
		i = 0;
		while (i < len)
		{
			*(dst2 + i) = *(src2 + i);
			i++;
		}
	}
	return (dst);
}
