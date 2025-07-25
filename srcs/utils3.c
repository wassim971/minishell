/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:27:38 by wbaali            #+#    #+#             */
/*   Updated: 2025/07/18 02:27:37 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_data *data, t_token *token)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token;
	if (tmp->type == CMD || (tmp->type == ARG && tmp->prev != data->token->prev
			&& tmp->prev->type > 5))
		count++;
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{
		if (tmp->type == CMD || (tmp->type == ARG
				&& tmp->prev != data->token->prev && tmp->prev->type > 5))
			count++;
		tmp = tmp->next;
	}
	return (count);
}
static int	add_to_cmd_param(char **cmd_param, int *i, char *str)
{
	cmd_param[*i] = ft_strdup(str);
	if (!cmd_param[*i])
		return (0);
	(*i)++;
	return (1);
}
static void	*free_cmd_param(char **cmd, int i)
{
	while (--i != -1)
		free(cmd[i]);
	free(cmd);
	return (NULL);
}

bool	check_pipe(t_data *data)
{
	if (data->token->type == PIPE)
	{
		write(2, "syntax error near unexpected token '|'\n", 39);
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (false);
	}
	return (true);
}

char	**get_param(t_data *data, t_token *token)
{
	char	**cmd_param;
	int		i;
	t_token	*tmp;

	i = 0;
	cmd_param = malloc(sizeof(char *) * (count_args(data, token) + 1));
	if (cmd_param == NULL)
		return (NULL);
	tmp = token;
	if (tmp->type != PIPE && (tmp->type == CMD || (tmp->type == ARG
				&& tmp->prev != data->token->prev && tmp->prev->type > 5))
		&& !add_to_cmd_param(cmd_param, &i, tmp->str))
		return (free_cmd_param(cmd_param, i));
	tmp = tmp->next;
	while (tmp != data->token && tmp->type != PIPE)
	{
		if ((tmp->type == CMD || (tmp->type == ARG
					&& tmp->prev != data->token->prev && tmp->prev->type > 5))
			&& !add_to_cmd_param(cmd_param, &i, tmp->str))
			return (free_cmd_param(cmd_param, i));
		tmp = tmp->next;
	}
	cmd_param[i] = NULL;
	return (cmd_param);
}
