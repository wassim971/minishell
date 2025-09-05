/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:27:38 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/05 20:24:02 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		if (tmp->type == CMD
			|| (tmp->type == ARG && tmp->prev != data->token->prev
				&& tmp->prev->type > 5))
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

// char	**get_param(t_data *data, t_token *token)
// {
// 	char		**cmd_param;
// 	int			i;
// 	t_token		*tmp;

// 	i = 0;
// 	cmd_param = malloc(sizeof(char *) * (count_args(data, token) + 1));
// 	if (cmd_param == NULL)
// 		return (NULL);
// 	tmp = token;
// 	if (tmp->type != PIPE
// 		&& (tmp->type == CMD
// 			|| (tmp->type == ARG && tmp->prev != data->token->prev
// 				&& tmp->prev->type > 5))
// 		&& !add_to_cmd_param(cmd_param, &i, tmp->str))
// 		return (free_cmd_param(cmd_param, i));
// 	tmp = tmp->next;
// 	while (tmp != data->token && tmp->type != PIPE)
// 	{
// 		if ((tmp->type == CMD
// 				|| (tmp->type == ARG && tmp->prev != data->token->prev
// 					&& tmp->prev->type > 5))
// 			&& !add_to_cmd_param(cmd_param, &i, tmp->str))
// 			return (free_cmd_param(cmd_param, i));
// 		tmp = tmp->next;
// 	}
// 	cmd_param[i] = NULL;
// 	return (cmd_param);
// }

static int	process_token(t_data *data, t_token *token,
					char **cmd_param, int *i)
{
	if ((token->type == CMD
			|| (token->type == ARG && token->prev != data->token->prev
				&& token->prev->type > 5))
		&& !add_to_cmd_param(cmd_param, i, token->str))
		return (0);
	return (1);
}

static int	fill_cmd_param(t_data *data, t_token *token,
					char **cmd_param, int *i)
{
	t_token	*tmp;

	tmp = token->next;
	while (tmp != data->token && tmp->type != PIPE)
	{
		if (!process_token(data, tmp, cmd_param, i))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

char	**get_param(t_data *data, t_token *token)
{
	char	**cmd_param;
	int		i;

	i = 0;
	cmd_param = malloc(sizeof(char *) * (count_args(data, token) + 1));
	if (!cmd_param)
		return (NULL);
	if (token->type != PIPE && !process_token(data, token, cmd_param, &i))
		return (free_cmd_param(cmd_param, i));
	if (!fill_cmd_param(data, token, cmd_param, &i))
		return (NULL);
	cmd_param[i] = NULL;
	return (cmd_param);
}
