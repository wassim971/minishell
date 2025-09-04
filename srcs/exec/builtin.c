/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:59:47 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/04 20:19:44 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	exec_builtin(int save_stdout, t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->cmd_param[0], INT_MAX))
		data->exit_code = ft_echo(cmd->cmd_param);
	else if (!ft_strncmp("cd", cmd->cmd_param[0], INT_MAX))
		data->exit_code = ft_cd(data, cmd->cmd_param);
	else if (!ft_strncmp("pwd", cmd->cmd_param[0], INT_MAX))
		data->exit_code = ft_pwd();
	else if (!ft_strncmp("export", cmd->cmd_param[0], INT_MAX))
		data->exit_code = ft_export(cmd->cmd_param, &data->env);
	else if (!ft_strncmp("unset", cmd->cmd_param[0], INT_MAX))
		data->exit_code = ft_unset(cmd->cmd_param, &data->env);
	else if (!ft_strncmp("env", cmd->cmd_param[0], INT_MAX))
		data->exit_code = ft_env(data->env);
	else if (!ft_strncmp("exit", cmd->cmd_param[0], INT_MAX))
	{
		if (cmd->outfile >= 0)
		{
			dup2(save_stdout, 1);
			close(save_stdout);
		}
		ft_exit(data, cmd->cmd_param);
	}
}

bool	launch_builtin(t_data *data, t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(1);
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	exec_builtin(save_stdout, data, cmd);
	if (save_stdout >= 0)
	{
		dup2(save_stdout, 1);
		close(save_stdout);
	}
	return (true);
}


