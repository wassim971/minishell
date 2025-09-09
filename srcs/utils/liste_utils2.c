/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:48:41 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/09 17:15:02 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static bool	read_in_stdin(t_data *data, int fd, char *word)
// {
// 	char	*buf;

// 	while (1)
// 	{
// 		buf = NULL;
// 		buf = readline("> ");
// 		if (!buf)
// 		{
// 			print_error("warning: here-document delimited by end-of-file ");
// 			print_error("(wanted '");
// 			print_error(word);
// 			print_error("')\n");
// 			if (data->token)
// 				free_token(&data->token);
// 			break ;
// 		}
// 		if (!ft_strncmp(word, buf, INT_MAX))
// 			break ;
// 		if (data->token->prev->type != 147 && !replace_dollars(&buf, data))
// 		{
// 			free(buf);
// 			free_all(data, MALLOC_ERROR, EXT_MALLOC);
// 		}
// 		write(fd, buf, ft_strlen(buf));
// 		write(fd, "\n", 1);
// 		free(buf);
// 	}
// 	free(buf);
// 	close(fd);
// 	return (true);
// }

static bool	process_line(t_data *data, int fd, char *word, char *buf)
{
	if (!ft_strncmp(word, buf, INT_MAX))
		return (false);
	if (data->token->prev->type != 147 && !replace_dollars(&buf, data))
	{
		free(buf);
		free_all(data, MALLOC_ERROR, EXT_MALLOC);
	}
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
	free(buf);
	return (true);
}

static bool	read_in_stdin(t_data *data, int fd, char *word)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
		{
			print_error("warning: here-document delimited by end-of-file ");
			print_error("(wanted '");
			print_error(word);
			print_error("')\n");
			if (data->token)
				free_token(&data->token);
			break ;
		}
		if (!process_line(data, fd, word, buf))
			break ;
	}
	close(fd);
	return (true);
}

static void	heredoc_sigint(int sig)
{
	t_data	*save;

	(void)sig;
	write(2, "> ^C\n", 5);
	save = get_data(NULL);
	if (save->cmd)
		free_cmd(&save->cmd);
	if (save->token)
		free_token(&save->token);
	if (save->env)
		free_list(&save->env);
	if (save->last_cmd)
		free(save->last_cmd);
	rl_clear_history();
	exit(130);
}

static int	heredoc_part(t_data *data, int fd, char *word)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		get_data(data);
		signal(SIGINT, heredoc_sigint);
		read_in_stdin(data, fd, word);
		close(fd);
		rl_clear_history();
		free_her(data);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(fd);
		waitpid(pid, &status, 0);
		if (status == 130 << 8)
			return (-1);
	}
	return (1);
}

int	here_doc(t_data *data, char *word)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (heredoc_part(data, fd, word) == -1)
	{
		data->exit_code = 130;
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd >= 0)
		unlink(".heredoc.tmp");
	signals();
	return (fd);
}
