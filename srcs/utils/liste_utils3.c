/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:01:24 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/05 20:18:45 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	condition(char *line, int i)
{
	if (!line[i] || !line[i + 1])
		return (false);
	if (line[i] != '$')
		return (false);
	if (line[i + 1] == '\'' || line[i + 1] == '"')
		return (false);
	if (!ft_isalpha(line[i + 1]) && line[i + 1] != '?')
		return (false);
	return (true);
}

t_data	*get_data(t_data *data)
{
	static t_data	*save;

	if (!data)
		return (save);
	save = data;
	return (NULL);
}

int	replace_dollars(char **line, t_data *data)
{
	bool	dq;
	int		i;
	char	*str;

	i = 0;
	dq = false;
	data->sq = false;
	str = ft_strdup("");
	while ((*line)[i])
	{
		if (condition((*line), i) && !add_dollar((*line), &i, &str, data))
			return (0);
		if ((*line)[i] && !add_chars(&(*line)[i], &str, data, &i))
			return (0);
	}
	free(*line);
	*line = &(*str);
	return (1);
}
