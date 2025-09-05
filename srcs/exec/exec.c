/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:19:29 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/05 17:33:18 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static void	parent_process(t_data *data, t_cmd *cmd, int *pip)
{
	close(pip[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->outfile >= 0)
		close(cmd->outfile);
	if (cmd->infile == -2)
		cmd->infile = pip[0];
	if (cmd->next != data->cmd && cmd->next->infile == -2)
		cmd->next->infile = pip[0];
	else
		close(pip[0]);
}

// static bool	exec_cmd(t_data *data, t_cmd *cmd, int *pip)
// {
// 	g_signal_pid = fork();
// 	if (g_signal_pid < 0)
// 		free_all(data, FORK_ERROR, EXT_FORK);
// 	else if (!g_signal_pid)
// 	{
// 		if (cmd->cmd_param && cmd->cmd_param[0])
// 			child_process(data, cmd, pip);
// 		else
// 			free_all(data, NULL, 0);
// 	}
// 	else
// 		parent_process(data, cmd, pip);
// 	return (true);
// }

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

static void	launch_child(t_data *data, t_cmd *cmd, int *pip)
{
	close_infile(cmd);
	get_data(data);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGPIPE, handle_sigpipe); 
	if (cmd->cmd_param && cmd->cmd_param[0])
		child_process(data, cmd, pip);
	else
	{
		data->exit_code = 1;
		free_all(data, NULL, data->exit_code);
	}
}

static bool	exec_cmd(t_data *data, t_cmd *cmd, int *pip)
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
		if(data->token)
			free_token(&data->token);
		launch_child(data, cmd, pip);
		free_all(data, NULL, data->exit_code);
	}
	else
	{
		get_cmd(cmd, 0);
		parent_process(data, cmd, pip);
	}
	return (true);
}

// static bool	exec_cmd(t_data *data, t_cmd *cmd, int *pip)
// {
// 	cmd->pid = fork();
// 	get_cmd(cmd, 0);
// 	if (cmd->pid < 0)
// 	{
// 		perror("fork");
// 		data->exit_code = 1;
// 		return (false);
// 	}
// 	else if (cmd->pid == 0)
// 	{
// 		close_infile(cmd);
// 		signal(SIGQUIT, SIG_DFL);
// 		signal(SIGINT, SIG_DFL);
// 		if (cmd->cmd_param && cmd->cmd_param[0])
// 			child_process(data, cmd, pip);
// 		else
// 		{
// 			data->exit_code = 1;
// 			free_all(data, NULL, 0);
// 		}
// 	}
// 	else
// 	{
// 		get_cmd(cmd, 0);
// 		parent_process(data, cmd, pip);
// 	}
// 	return (true);
// }

// static void	wait_all(t_data *data)
// {
// 	int		status;
// 	int		pid;
// 	int		len;
// 	t_cmd	*tmp;

// 	tmp = data->cmd;
// 	len = len_cmd(tmp);
// 	while (len--)
// 	{
// 		pid = waitpid(0, &status, 0);
// 		if (pid == g_signal_pid)
// 		{
// 			if (WIFEXITED(status))
// 				data->exit_code = WEXITSTATUS(status);
// 		}
// 		if (tmp->outfile >= 0)
// 			close(tmp->outfile);
// 		if (tmp->infile >= 0)
// 			close(tmp->infile);
// 		tmp = tmp->next;
// 	}
// }

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
// wait_all trop long
// void	wait_all(t_data *data)
// {
// 	int		status;
// 	t_cmd	*tmp;
// 	pid_t	pid;
// 	bool	jsp;
// 	int		sig;

// 	jsp = 1;
// 	tmp = data->cmd;
// 	while (jsp || tmp != data->cmd)
// 	{
// 		jsp = 0;
// 		pid = waitpid(tmp->pid, &status, 0);
// 		if (WIFSIGNALED(status))
// 		{
// 			sig = WTERMSIG(status);
// 			if (sig == SIGQUIT)
// 				write(2, "Quit (core dumped)\n", 19);
// 			data->exit_code = 131;
// 		}
// 		if (pid == tmp->pid && WIFEXITED(status) && data->exit_code != 130
// 			&& data->exit_code != 1)
// 			data->exit_code = WEXITSTATUS(status);
// 		if (tmp->outfile >= 0)
// 			close(tmp->outfile);
// 		if (tmp->infile >= 0)
// 			close(tmp->infile);
// 		tmp = tmp->next;
// 	}
// }

bool	exec(t_data *data)
{
	t_cmd	*tmp;
	int		*pip;

	pip = data->pip;
	tmp = data->cmd;
	if (tmp && tmp->skip_cmd == false && tmp->next == tmp && tmp->cmd_param[0]
		&& is_builtin(tmp->cmd_param[0]))
		return (launch_builtin(data, tmp));
	if (pipe(pip) == -1)
		return (false);
	exec_cmd(data, tmp, pip);
	tmp = tmp->next;
	while (tmp != data->cmd)
	{
		if (pipe(pip) == -1)
			return (-1);
		exec_cmd(data, tmp, pip);
		tmp = tmp->next;
	}
	wait_all(data);
	return (true);
}
