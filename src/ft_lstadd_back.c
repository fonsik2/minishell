/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smdyan <smdyan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:29:58 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/11 17:30:01 by smdyan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*el;

	if (!new || !lst)
		return (1);
	if (!(*lst))
	{
		*lst = new;
		return (0);
	}
	el = *lst;
	while (el->next)
		el = el->next;
	el->next = new;
	return (0);
}
