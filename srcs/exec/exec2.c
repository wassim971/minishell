/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 19:16:07 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/09 14:36:48 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_infile(t_cmd *cmd)
{
	t_cmd	*save;

	save = cmd;
	cmd = cmd->next;
	while (cmd != save)
	{
		if (cmd->infile > 0)
			close(cmd->infile);
		cmd->infile = -2;
		if (cmd->outfile > 0)
			close(cmd->outfile);
		cmd->outfile = -2;
		cmd = cmd->next;
	}
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp("echo", cmd, INT_MAX) || !ft_strncmp("cd", cmd, INT_MAX)
		|| !ft_strncmp("pwd", cmd, INT_MAX) || !ft_strncmp("export", cmd,
			INT_MAX) || !ft_strncmp("unset", cmd, INT_MAX) || !ft_strncmp("env",
			cmd, INT_MAX) || !ft_strncmp("exit", cmd, INT_MAX))
		return (true);
	return (false);
}

void	parent_process(t_data *data, t_cmd *cmd)
{
	close(cmd->pip[1]);
	if (cmd->next != data->cmd && cmd->next->skip_cmd == false)
		cmd->next->fd_transfert = cmd->pip[0];
	else
		close(cmd->pip[0]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	if (cmd->fd_transfert != -1)
		close(cmd->fd_transfert);
}
