/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:43:02 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/08 18:39:56 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static void	read_from_pipe(int fd)
// {
// 	char	buffer[1024];
// 	ssize_t	bytes_read;
// 	ssize_t	written;

// 	printf("je suis l %d\n", fd);
// 	while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
// 	{
// 		written = write(STDOUT_FILENO, buffer, bytes_read);
// 		if (written == -1)
// 		{
// 			perror("write");
// 			break ;
// 		}
// 	}
// 	if (bytes_read == -1)
// 		perror("read");
// 	close(fd);
// }

static bool	check_dir(char **path, char *cmd, t_data *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		print_error(cmd);
		print_error(" : Is a directory\n");
		data->exit_code = 126;
		return (false);
	}
	return (true);
}

static bool	cmd_exist(char **path, t_data *data, char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		*path = find_cmd(data, cmd, data->env);
	else
		absolute_path(path, cmd, data);
	if (!(*path) && data->exit_code == -1)
		free_all(data, NULL, data->exit_code);
	if (!(*path))
	{
		data->exit_code = 127;
		return (false);
	}
	if (access((*path), X_OK))
	{
		perror(*path);
		free((*path));
		(*path) = NULL;
		data->exit_code = 126;
		return (false);
	}
	if (!check_dir(path, cmd, data))
		return (false);
	return (true);
}

static void	redirect_in_out(t_data *data, t_cmd *cmd)
{
	close(cmd->pip[0]);
	if (cmd->infile >= 0)
	{
		if (cmd->fd_transfert >= 0)
			close(cmd->fd_transfert);
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	else if (cmd != data->cmd && cmd->fd_transfert)
	{
		dup2(cmd->fd_transfert, 0);
		close(cmd->fd_transfert);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else
	{
		if (cmd->next != data->cmd)
			dup2(cmd->pip[1], 1);
	}
	close(cmd->pip[1]);
}

static void	built(t_cmd *cmd, t_data *data)
{
	close(cmd->pip[0]);
	if (cmd->outfile < 0 && cmd->next != data->cmd)
		cmd->outfile = cmd->pip[1];
	else
		close(cmd->pip[1]);
	launch_builtin(data, cmd);
}

void	child_process(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	**env;

	path = NULL;
	if (cmd->skip_cmd)
		data->exit_code = 1;
	else if (is_builtin(cmd->cmd_param[0]))
		built(cmd, data);
	else if (cmd_exist(&path, data, cmd->cmd_param[0]))
	{
		redirect_in_out(data, cmd);
		env = lst_to_arr(data->env);
		if (!env)
			free_all(data, MALLOC_ERROR, EXT_MALLOC);
		rl_clear_history();
		signals2();
		execve(path, cmd->cmd_param, env);
		data->exit_code = 1;
		perror(path);
		free(env);
	}
	if (path)
		free(path);
	free_all(data, NULL, data->exit_code);
}
