/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liste_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 02:48:41 by wbaali            #+#    #+#             */
/*   Updated: 2025/08/22 16:10:27 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	condition(char *line, int i)
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
		if ((*line)[i] && !add_char(&(*line)[i], &str, data, &i))
			return (0);
	}
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
			break ;
		}
		if (!ft_strncmp(word, buf, INT_MAX))
			break ;
		if (data->token->prev->type != 147 && !replace_dollars(&buf, data))
			free_all(data, MALLOC_ERROR, EXT_MALLOC);
		printf("str : %s\n", buf);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
	close(fd);
	return (true);
}

int	here_doc(t_data *data, char *word)
{
	int	fd;

	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_in_stdin(data, fd, word))
	{
		unlink(".heredoc.tmp");
		return (-1);
	}
	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd > 0)
		unlink(".heredoc.tmp");
	return (fd);
}
