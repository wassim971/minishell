/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:08:31 by wbaali            #+#    #+#             */
/*   Updated: 2025/07/25 19:00:04 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_substr(char **dest, char *src, int len)
{
	char	*tmp;
	char	*substr;

	substr = ft_substr(src, 0, len);
	if (!substr)
		return (0);
	tmp = ft_strjoin(*dest, substr);
	free(substr);
	free(*dest);
	*dest = tmp;
	if (!*dest)
		return (0);
	return (1);
}

int	exist_in_env(char *line, int *i, t_data *data)
{
	t_mini_list	*tmp;
	t_mini_list	*start;
	int			var_len;

	if (line[*i + 1] == '?' || line[*i + 1] == '$')
		return (2);
	tmp = data->env;
	start = tmp;
	while (tmp)
	{
		var_len = ft_strchr(tmp->str, '=') - tmp->str;
		if (ft_strncmp(tmp->str, &line[*i + 1], var_len) == 0
			&& !ft_isalnum(line[*i + 1 + var_len]) && line[*i + 1
			+ var_len] != '_')
		{
			*i += var_len + 1;
			return (1);
		}
		tmp = tmp->next;
		if (tmp == start)
			break ;
	}
	while (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_')
		(*i)++;
	(*i)++;
	return (0);
}
