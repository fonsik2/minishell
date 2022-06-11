/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:05:37 by smdyan            #+#    #+#             */
/*   Updated: 2021/11/08 11:08:09 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	size_t			slen;
	size_t			size;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		size = 0;
	else if ((slen - start) > len)
		size = len;
	else
		size = slen - start;
	sub = (char *) malloc(size + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, (s + start), (size + 1));
	return (sub);
}
