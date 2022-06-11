/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:03:16 by smdyan            #+#    #+#             */
/*   Updated: 2021/11/03 21:52:19 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	asize(char const *s, char c)
{
	size_t	n;
	size_t	i;

	if (!*s)
		return (0);
	n = 0;
	i = 1;
	while (*(s + i))
	{
		if (*(s + i) == c && *(s + i - 1) != c)
			n++;
		i++;
	}
	if (*(s + i - 1) != c)
		n++;
	return (n);
}

static void	set_delim(size_t *d, char const *s, char c)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (*(s + i))
	{
		if (*(s + i) != c && (n % 2) == 0)
		{
			*(d + n) = i;
			n++;
		}
		else if (*(s + i) == c && (n % 2) == 1)
		{
			*(d + n) = i - *(d + n - 1);
			n++;
		}
		i++;
	}
	if (*s && i && *(s + i - 1) != c)
		*(d + n) = i - *(d + n - 1);
}

static int	afree(size_t *d, char **a, int i)
{
	if (!d)
		return (1);
	if (!a && d)
	{
		free(d);
		return (1);
	}
	if (i != -1 && a && !(*(a + i)))
	{
		while (i > 0)
		{
			free(*(a + i - 1));
			i--;
		}
		free(a);
		free(d);
		return (1);
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	n;
	size_t	i;
	char	**a;
	size_t	*d;

	if (!s)
		return (NULL);
	n = asize(s, c);
	d = (size_t *)malloc(sizeof (size_t) * n * 2);
	a = (char **)malloc(sizeof (char *) * (n + 1));
	if (afree(d, a, -1))
		return (NULL);
	set_delim(d, s, c);
	i = 0;
	while (i < n)
	{
		*(a + i) = (char *)malloc(sizeof (char) * *(d + (i * 2 + 1)) + 1);
		if (afree(d, a, (int)i))
			return (NULL);
		ft_strlcpy(*(a + i), s + *(d + i * 2), *(d + (i * 2 + 1)) + 1);
		i++;
	}
	*(a + i) = NULL;
	free(d);
	return (a);
}
