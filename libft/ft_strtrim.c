/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 13:00:24 by smdyan            #+#    #+#             */
/*   Updated: 2021/11/03 21:50:16 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check(char const *ch, char const *set)
{
	size_t	i;

	i = 0;
	while (*(set + i))
	{
		if (*ch == *(set + i))
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*st;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (start < ft_strlen(s1))
	{
		if (!check((s1 + start), set))
			break ;
		start++;
	}
	end = ft_strlen(s1) - 1;
	while (end >= start)
	{
		if (!check((s1 + end), set))
			break ;
		end--;
	}
	st = (char *) malloc(end - start + 2);
	if (!st)
		return (NULL);
	ft_strlcpy(st, (s1 + start), (end - start + 2));
	return (st);
}
