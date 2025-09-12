/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:19:29 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/12 15:35:44 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	launch_child(t_data *data, t_cmd *cmd)
{
	close_infile(cmd);
	get_data(data);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, handle_sigpipe);
	if (cmd->cmd_param && cmd->cmd_param[0])
		child_process(data, cmd);
	else
	{
		close(cmd->pip[0]);
		close(cmd->pip[1]);
		data->exit_code = 1;
		free_all(data, NULL, data->exit_code);
	}
}

static bool	exec_cmd(t_data *data, t_cmd *cmd)
{
	cmd->pid = fork();
	get_cmd(cmd, 0);
	if (cmd->pid < 0)
	{
		perror("fork");
		data->exit_code = 1;
		return (false);
	}
	else if (cmd->pid == 0)
	{
		if (data->token)
			free_token(&data->token);
		launch_child(data, cmd);
		if (cmd->fd_transfert != -1)
			close(cmd->fd_transfert);
		free_all(data, NULL, data->exit_code);
	}
	else
	{
		get_cmd(cmd, 0);
		parent_process(data, cmd);
	}
	return (true);
}

static void	handle_child_status(t_data *data, int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		data->exit_code = 128 + sig;
	}
	else if (WIFEXITED(status) && data->exit_code != 130)
		data->exit_code = WEXITSTATUS(status);
}

void	wait_all(t_data *data)
{
	int		status;
	t_cmd	*tmp;
	pid_t	pid;
	bool	first;

	first = true;
	tmp = data->cmd;
	while (first || tmp != data->cmd)
	{
		first = false;
		pid = waitpid(tmp->pid, &status, 0);
		handle_child_status(data, status);
		if (tmp->outfile >= 0)
			close(tmp->outfile);
		if (tmp->infile >= 0)
			close(tmp->infile);
		tmp = tmp->next;
	}
}

bool	exec(t_data *data)
{
	t_cmd	*tmp;

	tmp = data->cmd;
	if (tmp && tmp->skip_cmd == false && tmp->next == tmp && tmp->cmd_param[0]
		&& is_builtin(tmp->cmd_param[0]))
		return (launch_builtin(data, tmp));
	if (pipe(tmp->pip) == -1)
		return (false);
	exec_cmd(data, tmp);
	tmp = tmp->next;
	while (tmp != data->cmd)
	{
		if (pipe(tmp->pip) == -1)
			return (-1);
		exec_cmd(data, tmp);
		tmp = tmp->next;
	}
	wait_all(data);
	return (true);
}
