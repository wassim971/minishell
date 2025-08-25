/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:43:33 by wbaali            #+#    #+#             */
/*   Updated: 2025/08/21 13:54:30 by wbaali           ###   ########.fr       */
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
