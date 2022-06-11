/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 11:28:33 by smdyan            #+#    #+#             */
/*   Updated: 2021/10/28 16:30:38 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	size_t	i;
	size_t	j;

	h = (char *)haystack;
	n = (char *)needle;
	if (*n == '\0' || n == 0)
		return (h);
	i = 0;
	while (*(h + i) && i < len)
	{
		j = 0;
		while (*(h + i + j) == *(n + j) && (i + j) < len)
		{
			if (*(n + j + 1) == '\0')
				return (h + i);
			j++;
		}
		i++;
	}
	return (0);
}
