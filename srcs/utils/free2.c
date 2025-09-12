/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:58:32 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/12 15:37:18 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	arr = NULL;
}

void	free_part(t_data *data)
{
	if (data->cmd)
		free_cmd(&data->cmd);
	if (data->token)
		free_token(&data->token);
}

void	free_her(t_data *data)
{
	if (data->cmd)
		free_cmd(&data->cmd);
	if (data->token)
		free_token(&data->token);
	if (data->env)
		free_list(&data->env);
	if (data->last_cmd)
		free(data->last_cmd);
}

void	get_close_pip(t_cmd *cmd)
{
	if (cmd->pip[0] != -1)
		close(cmd->pip[0]);
	if (cmd->pip[1] != -1)
		close(cmd->pip[1]);
	if (cmd->fd_transfert != -1)
		close(cmd->fd_transfert);
}

void	fin_child(char *path, char **env, t_data *data)
{
	data->exit_code = 1;
	perror(path);
	free(env);
}
