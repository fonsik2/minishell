/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:54:22 by smdyan            #+#    #+#             */
/*   Updated: 2021/11/03 13:43:48 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))

{
	unsigned int	i;
	unsigned int	j;
	char			*tmp_st;
	char			tmp_ch;

	if (!f || !s)
		return (NULL);
	tmp_st = (char *)malloc(sizeof (char) * (ft_strlen(s) + 1));
	if (!tmp_st)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		tmp_ch = f(i, *(s + i));
		if (tmp_ch)
		{
			*(tmp_st + j) = tmp_ch;
			j++;
		}
		i++;
	}
	*(tmp_st + j) = '\0';
	return (tmp_st);
}
