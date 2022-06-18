/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:27:11 by smdyan            #+#    #+#             */
/*   Updated: 2022/06/18 19:10:34 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_name(t_env *new, char *str, int *i, char c)
{
	int	len;

	while (str[(*i)] != c)
		(*i)++;
	new->name = (char *)malloc(sizeof(char) * ((*i) + 1));
	if (!new->name)
		return (1);
	len = (*i);
	*i = 0;
	while (len-- > 0)
	{
		new->name[*i] = str[*i];
		(*i)++;
	}
	new->name[*i] = '\0';
	return (0);
}

static void	*shlvl_plus_one(t_env *new)
{
	int	lvl;

	lvl = ft_atoi(new->value);
	if (lvl < 0)
		lvl = 0;
	else if (lvl >= 999)
	{
		lvl = 1;
		ft_putstr_fd("minishell: warning: "
			"shell level (1000) too high, resetting to 1\n", 2);
	}
	else
		lvl++;
	free(new->value);
	new->value = ft_itoa(lvl);
	if (!(new->value))
		return (NULL);
	return (new->value);
}

static void	new_value(t_env *new, int len, char *str, int j)
{
	int	i;

	i = 0;
	while (len-- > 0)
		new->value[i++] = str[j++];
	new->value[i] = '\0';
	new->next = NULL;
	new->index = 0;
}

t_env	*ft_lstnew(char *str, int i)
{
	t_env	*new;
	int		j;
	int		len;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	if (get_name(new, str, &i, '='))
		return (NULL);
	len = 0;
	j = ++i;
	while (str[i++])
		len++;
	new->value = (char *)malloc(sizeof(char) * (len + 1));
	if (!new->value)
		return (NULL);
	new_value(new, len, str, j);
	if (ft_strncmp(new->name, "SHLVL", 5) == 0)
	{
		if (!shlvl_plus_one(new))
			return (NULL);
	}
	return (new);
}

int	envp_to_list(t_all *all, char **envp)
{
	int	i;

	i = -1;
	if (!envp)
		return (1);
	while (envp[++i])
	{
		if (ft_lstadd_back(&all->list_envp, ft_lstnew(envp[i], 0)) == 1)
		{
			envp_list_free(all);
			return (1);
		}
	}
	return (0);
}
