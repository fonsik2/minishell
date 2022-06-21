/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:54:40 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/20 20:59:22 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static long int	define_sig(const char *str, int *i)
{
	long int	sig;

	sig = 1;
	if (*(str + *i) == '+')
		*i = *i + 1;
	else if (*(str + *i) == '-')
	{
		sig = sig * (-1);
		*i = *i + 1;
	}
	while (*(str + *i) == '0')
		*i = *i + 1;
	return (sig);
}

int	ft_atoi(const char *str)
{
	long int	n;
	long int	nn;
	int			i;
	long int	sig;

	i = 0;
	while (*(str + i) == 32 || (*(str + i) >= 9 && *(str + i) <= 13))
		i++;
	sig = define_sig(str, &i);
	n = 0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		nn = n;
		n = n * 10 + (*(str + i) - 48);
		if ((nn < 0 && n > 0) || (nn > 0 && n < 0))
		{
			if (sig == -1)
				return (0);
			if (sig == 1)
				return (-1);
		}
		i++;
	}
	n *= sig;
	return (n);
}
