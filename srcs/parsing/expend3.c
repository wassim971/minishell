/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:26:02 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/05 19:27:07 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_dollar_word(char *line, int size)
{
	char	*dollar;
	int		i;

	dollar = malloc(sizeof(char) * size);
	if (!dollar)
		return (NULL);
	i = 0;
	while (line[++i] && i < size)
	{
		dollar[i - 1] = line[i];
	}
	dollar[i - 1] = '\0';
	return (dollar);
}

char	*get_elem_env(t_mini_list *env, char *key)
{
	t_mini_list	*tmp;
	int			len;
	int			t;

	if (!key)
		return (NULL);
	tmp = env;
	len = len_list(tmp);
	t = ft_strlen(key);
	while (len--)
	{
		if (ft_strncmp(tmp->str, key, t) == 0)
		{
			len = 0;
			while (tmp->str[len])
				if (tmp->str[len++] == '=')
					break ;
			return (ft_strdup(&(tmp->str[len])));
		}
		tmp = tmp->next;
	}
	return (NULL);
}
