/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:01:35 by smdyan            #+#    #+#             */
/*   Updated: 2021/11/03 21:55:55 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_neg(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static int	set_len(int n)
{
	int	i;

	i = 0;
	if (check_neg(n))
	{
		n = n * (-1);
		i++;
	}
	if (!n)
		i++;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	convert(int i, char *str, int a)
{
	char	fig;
	int		dig;

	if (check_neg(a))
	{
		*(str + i) = '-';
		i++;
	}
	dig = a % 10;
	if (check_neg(dig))
		dig = dig * (-1);
	fig = dig + '0';
	a = a / 10;
	if (check_neg(a))
		a = a * (-1);
	if (a)
		i = convert(i, str, a);
	*(str + i) = fig;
	i++;
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = set_len(n);
	str = (char *)malloc(sizeof (char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	i = convert(i, str, n);
	*(str + i) = '\0';
	return (str);
}
