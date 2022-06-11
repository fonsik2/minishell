/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:18:22 by smdyan            #+#    #+#             */
/*   Updated: 2021/11/08 09:56:00 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ch_minus(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	fig;
	int		dig;

	if (!fd)
		return ;
	if (ch_minus(n))
		write(fd, "-", 1);
	dig = n % 10;
	if (ch_minus(dig))
		dig = dig * (-1);
	fig = dig + '0';
	n = n / 10;
	if (ch_minus(n))
		n = n * (-1);
	if (n)
		ft_putnbr_fd(n, fd);
	write(fd, &fig, 1);
}
