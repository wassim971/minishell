/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:48:41 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/04 17:11:17 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	condition(char *line, int i)
{
	if (!line[i] || !line[i + 1])
		return (false);
	if (line[i] != '$')
		return (false);
	if (line[i + 1] == '\'' || line[i + 1] == '"')
		return (false);
	if (!ft_isalpha(line[i + 1]) && line[i + 1] != '?')
		return (false);
	return (true);
}

static int	replace_dollars(char **line, t_data *data)
{
	bool	dq;
	int		i;
	char	*str;

	i = 0;
	dq = false;
	data->sq = false;
	str = ft_strdup("");
	while ((*line)[i])
	{
		if (condition((*line), i) && !add_dollar((*line), &i, &str, data))
			return (0);
		if ((*line)[i] && !add_chars(&(*line)[i], &str, data, &i))
			return (0);
	}
	free(*line);
	*line = &(*str);
	return (1);
}

static bool	read_in_stdin(t_data *data, int fd, char *word)
{
	char	*buf;

	while (1)
	{
		buf = NULL;
		buf = readline("> ");
		if (!buf)
		{
			print_error("warning: here-document delimited by end-of-file ");
			print_error("(wanted '");
			print_error(word);
			print_error("')\n");
			free(buf);
			break ;
		}
		if (!ft_strncmp(word, buf, INT_MAX))
			break ;
		if (data->token->prev->type != 147 && !replace_dollars(&buf, data))
		{
			free(buf);
			free_all(data, MALLOC_ERROR, EXT_MALLOC);
		}
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
	close(fd);
	return (true);
}

// int	here_doc(t_data *data, char *word)
// {
// 	int	fd;

// 	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd < 0)
// 		return (-1);
// 	if (!read_in_stdin(data, fd, word))
// 	{
// 		unlink(".heredoc.tmp");
// 		return (-1);
// 	}
// 	fd = open(".heredoc.tmp", O_RDONLY);
// 	if (fd > 0)
// 		unlink(".heredoc.tmp");
// 	return (fd);
// }
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
	if (save->pip[0] && save->pip[0] != -1)
		close(save->pip[0]);
	if (save->pip[1] && save->pip[1] != -1)
		close(save->pip[1]);
	if (save->last_cmd)
		free(save->last_cmd);
	rl_clear_history();
	exit(130);
}

t_data	*get_data(t_data *data)
{
	static t_data	*save;

	if (!data)
		return (save);
	save = data;
	return (NULL);
}

int	here_doc(t_data *data, char *word)
{
	int		fd;
	pid_t	pid;
	int		status;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		get_data(data);
		signal(SIGINT, heredoc_sigint);
		read_in_stdin(data, fd, word);
		close(fd);
		rl_clear_history();
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		close(fd);
		waitpid(pid, &status, 0);
		if (status == 130 << 8)
		{
			data->exit_code = 130;
			unlink(".heredoc.tmp");
			return (-1);
		}
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd >= 0)
		unlink(".heredoc.tmp");
	signals();
	return (fd);
}
