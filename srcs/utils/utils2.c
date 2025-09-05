/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:43:33 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/05 19:43:46 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t'
			|| c == '\v'))
		return (true);
	return (false);
}

int	is_special(char *str)
{
	if (str && *str && ft_strlen(str) >= 2)
	{
		if (!ft_strncmp(str, "<<", 2))
			return (HEREDOC);
		if (!ft_strncmp(str, ">>", 2))
			return (APPEND);
	}
	if (*str && ft_strlen(str) >= 1)
	{
		if (!ft_strncmp(str, "<", 1))
			return (INPUT);
		if (!ft_strncmp(str, ">", 1))
			return (TRUNC);
		if (!ft_strncmp(str, "|", 1))
			return (PIPE);
	}
	return (0);
}

int	ft_strlen_exp(char *line)
{
	int	i;

	i = 1;
	if (line[i] == '_')
		return (i + 1);
	while (line[i] && (ft_isalpha(line[i]) && line[i] != '_'))
		i++;
	if (i == 1)
		return (i - 1);
	return (i);
}

char	*ft_strjoin_frees(char *s1, char *s2)
{
	char	*tmp;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		tmp = ft_strdup(s1);
		free(s1);
		return (tmp);
	}
	tmp = ft_strjoin(s1, s2);
	free(s2);
	return (tmp);
}

size_t	len_list(t_mini_list *list)
{
	t_mini_list	*tmp;
	size_t		i;

	if ((list))
	{
		tmp = list;
		i = 1;
		while (tmp->next != list)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}
