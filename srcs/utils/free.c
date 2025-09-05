/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:56:42 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/05 17:03:45 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	free_all_cmd(t_cmd *tmp)
{
	if (tmp->infile > 0)
		close(tmp->infile);
	tmp->infile = -2;
	if (tmp->outfile > 0)
		close(tmp->outfile);
	tmp->outfile = -2;
	free_array(tmp->cmd_param);
}

void	free_cmd(t_cmd **list)
{
	t_cmd	*tmp;
	t_cmd	*current;

	if (!(*list))
		return ;
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free_all_cmd(tmp);
		free(tmp);
	}
	free_all_cmd(current);
	free(current);
	*list = NULL;
	get_cmd(NULL, 1);
}

void	free_token(t_token **list)
{
	t_token	*tmp;
	t_token	*current;

	if (!(*list))
		return ;
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
	}
	free(current->str);
	free(current);
	*list = NULL;
}

int	free_list(t_mini_list **list)
{
	t_mini_list	*tmp;
	t_mini_list	*current;

	if (!(*list))
		return (0);
	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free(tmp->str);
		free(tmp);
	}
	free(current->str);
	free(current);
	*list = NULL;
	return (0);
}

void	free_all(t_data *data, char *err, int ext)
{
	if (data->cmd)
		free_cmd(&data->cmd);
	if (data->token)
		free_token(&data->token);
	if (data->env)
		free_list(&data->env);
	if (data->pip[0] && data->pip[0] != -1)
		close(data->pip[0]);
	if (data->pip[1] && data->pip[1] != -1)
		close(data->pip[1]);
	if (data->last_cmd)
		free(data->last_cmd);
	if (err)
		print_error(err);
	rl_clear_history();
	if (!access(".heredoc.tmp", F_OK))
		unlink(".heredoc.tmp");
	if (ext != -1)
	{
		rl_clear_history();
		exit(ext);
	}
}
