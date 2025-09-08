/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:27:47 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/08 15:44:18 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	quoting_choice(bool *dq, bool *sq, int *index, char c)
{
	if ((c == '\'' || c == '"') && !*sq && !*dq)
	{
		if (c == '\'' && !*dq)
			*sq = true;
		else if (c == '"' && !*sq)
			*dq = true;
		if (index)
			++(*index);
	}
	else if ((c == '\'' || c == '"'))
	{
		if (c == '\'' && !*dq && *sq)
			*sq = false;
		else if (c == '"' && !*sq && *dq)
			*dq = false;
		if (index)
			++(*index);
	}
}

int	open_quote(t_data *data, char *line)
{
	bool	dq;
	bool	sq;
	int		i;

	i = 0;
	dq = false;
	sq = false;
	while (line && line[i])
	{
		quoting_choice(&dq, &sq, &i, line[i]);
		if (line[i] && line[i] != '\'' && line[i] != '"')
			++i;
	}
	if (dq || sq)
	{
		print_error("open quote\n");
		data->exit_code = 2;
		return (1);
	}
	return (0);
}

bool	condition1(char *line, int i)
{
	if (!line[i] || !line[i + 1])
		return (false);
	if (line[i] != '$')
		return (false);
	if (line[i + 1] == '\'' || line[i + 1] == '"')
		return (false);
	if (!ft_isalpha(line[i + 1]) && line[i + 1] != '?' && line[i + 1] != '_')
		return (false);
	return (true);
}

int	replace_dollar(char **line, t_data *data)
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
		quoting_choice(&dq, &data->sq, NULL, (*line)[i]);
		if (condition1((*line), i) && !data->sq && !add_dollar((*line), &i,
				&str, data))
			return (0);
		if ((*line)[i] && !add_char(&(*line)[i], &str, data, &i))
			return (0);
	}
	free(*line);
	*line = &(*str);
	return (1);
}

// bool	parseline(t_data *data, char *line)
// {
// 	if (open_quote(data, line))
// 	{
// 		free(line);
// 		return (false);
// 	}
// 	if (!replace_dollar(&line, data) || !create_list_token(&data->token, line))
// 	{
// 		if (line[0] == '\0')
// 		{
// 			free(line);
// 			return (false);
// 		}
// 		free(line);
// 		free_all(data, MALLOC_ERROR, EXT_MALLOC);
// 	}
// 	free(line);
// 	free(data->last_cmd);
// 	data->last_cmd = ft_strdup(data->token->prev->str);
// 	if (data->token && data->token->prev->type == PIPE)
// 	{
// 		write(2, "Error: Unclosed pipe\n", 21);
// 		data->exit_code = 2;
// 		free_token(&data->token);
// 		return (false);
// 	}
// 	if (!data->token || !create_list_cmd(data))
// 	{
// 		free_token(&data->token);
// 		free_cmd(&data->cmd);
// 		return (false);
// 	}
// 	return (check_pipe(data));
// }

bool	parseline(t_data *data, char *line)
{
	if (open_quote(data, line))
		return (free(line), false);
	if (!replace_dollar(&line, data) || !create_list_token(&data->token, line))
	{
		if (line[0] == '\0')
			return (free(line), false);
		free(line);
		free_all(data, MALLOC_ERROR, EXT_MALLOC);
	}
	free(line);
	// if (data->last_cmd)
	free(data->last_cmd);
	data->last_cmd = ft_strdup(data->token->prev->str);
	if (data->token && data->token->prev->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_code = 2;
		free_token(&data->token);
		return (false);
	}
	if (!data->token || !create_list_cmd(data))
		return (free_token(&data->token), free_cmd(&data->cmd), false);
	return (check_pipe(data));
}
