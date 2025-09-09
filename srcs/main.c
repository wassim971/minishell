/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:33 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/09 17:12:05 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_data(t_data *data)
{
	data->env = NULL;
	data->token = NULL;
	data->cmd = NULL;
	data->last_cmd = NULL;
	data->exit_code = 0;
	signals();
}

static int	casspe(int ac, char **av)
{
	(void)ac;
	(void)av;
	if (!isatty(STDOUT_FILENO))
	{
		write(STDERR_FILENO,
			"Qu'est-ce que tu fais,chef ? Tu veux me mettre 0 ou quoi ?\n", 59);
		return (1);
	}
	return (0);
}

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

static void	shell_loop(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("minironflex> ");
		if (!line)
			free_all(data, "exit\n", data->exit_code);
		if (empty_line(line))
			continue ;
		add_history(line);
		if (!parseline(data, line))
			continue ;
		if (!exec(data))
		{
			free(line);
			free_all(data, PIPE_ERROR, EXT_PIPE);
		}
		free_part(data);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (casspe(ac, av))
		return (1);
	init_data(&data);
	if (!make_env(&data, env))
		free_all(&data, MALLOC_ERROR, EXT_MALLOC);
	update_shlvl(&data);
	shell_loop(&data);
	return (0);
}
