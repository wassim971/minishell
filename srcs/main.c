/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:33 by wbaali            #+#    #+#             */
/*   Updated: 2025/08/26 15:02:25 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

pid_t	g_signal_pid;

void	init_data(t_data *data)
{
	data->env = NULL;
	data->token = NULL;
	data->cmd = NULL;
	data->last_cmd = NULL;
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

// static int	casspe(int ac, char **av)
// {
// 	(void)ac;
// 	(void)av;
// 	if (!isatty(STDOUT_FILENO))
// 	{
// 		write(STDERR_FILENO,
// 			"Qu'est-ce que tu fais,chef ? Tu veux me ***** ou quoi ?\n", 56);
// 		return (1);
// 	}
// 	return (0);
// }

void	update_shlvl(t_data *data)
{
	char		*shlvl;
	char		*new_shlvl;
	int			level;
	t_mini_list	*node;

	node = data->env;
	while (node)
	{
		if (ft_strncmp(node->str, "SHLVL=", 6) == 0)
		{
			shlvl = node->str + 6;
			level = ft_atoi(shlvl) + 1;
			free(node->str);
			new_shlvl = ft_itoa(level);
			new_shlvl = ft_strjoin_frees("SHLVL=", new_shlvl);
			if (!new_shlvl)
				free_all(data, MALLOC_ERROR, EXT_MALLOC);
			node->str = new_shlvl;
			return ;
		}
		node = node->next;
	}
	new_shlvl = ft_strdup("SHLVL=1");
	if (!new_shlvl || !append(&(data->env), new_shlvl))
		free_all(data, MALLOC_ERROR, EXT_MALLOC);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*line;

	// if (casspe(ac, av))
	// 	return (1);
	(void)ac;
	(void)av;
	init_data(&data);
	if (!make_env(&data, env))
		free_all(&data, MALLOC_ERROR, EXT_MALLOC);
	update_shlvl(&data);
	while (1)
	{
		line = readline("minironflex> ");
		if (!line)
			free_all(&data, "exit\n", data.exit_code);
		if (empty_line(line))
			continue ;
		add_history(line);
		if (!parseline(&data, line))
			continue ;
		if (!exec(&data))
			free_all(&data, PIPE_ERROR, EXT_PIPE);
		free_part(&data);
		g_signal_pid = 0;
	}
	free_all(&data, NULL, -1);
	return (0);
}
