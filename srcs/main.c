/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:33 by wbaali            #+#    #+#             */
/*   Updated: 2025/07/18 03:14:56 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t	g_signal_pid;

void	init_data(t_data *data)
{
	data->env = NULL;
	data->token = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	data->pip[0] = -1;
	data->pip[1] = -1;
	g_signal_pid = 0;
	signals();
}
bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*line;

	(void)ac;
	(void)av;
	init_data(&data);
	if (!make_env(&data, env))
		free_all(&data, MALLOC_ERROR, EXT_MALLOC);
	while (1)
	{
		line = readline("minirex> ");
		if (!line)
			free_all(&data, "exit\n", data.exit_code);
		if (empty_line(line))
			continue ;
		add_history(line);
		if (!parseline(&data, line))
			continue ;
	}
}
