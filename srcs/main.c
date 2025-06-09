/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wassim <wassim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:33 by wbaali            #+#    #+#             */
/*   Updated: 2025/06/08 14:46:05 by wassim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

char	*get_exp(char *cmd, t_mini base, int len)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(base.input[i], cmd, len) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

char *ft_strndup_range(const char *s, int start, int end)
{
    int len;
    char *sub;
    int i;

    if (!s || start < 0 || end < start)
        return NULL;
    len = end - start;
    sub = malloc(sizeof(char) * (len + 1));
    if (!sub)
        return NULL;
    i = 0;
    while (start < end && s[start])
        sub[i++] = s[start++];
    sub[i] = '\0';
    return sub;
}

void	parsexp(t_mini base, int i)
{
	int start;
	char *expend;

	start = i;
	if (base.input[i] == '\'')
		return;
	while (ft_isalnum(base.input[i]) || base.input[i] == '_')
		i++;
	if (start != i)
	{
		expend = ft_strndup_range(base.input, start, i);
		expend = get_exp(expend,base,(i - start));
	}
}

int	parsdq(t_mini base, int i)
{
	while (base.input[i] && base.input[i] != '"')
	{
		if (base.input[i] == '$')
			parsexp(base, ++i);
		i++;
	}
	if (base.input[i] == '\0')
		return (0);
	return (i);
}

void	parsing(t_mini base)
{
	int	i;

	i = 0;
	while (base.input[i])
	{
		if (base.input[i] == '"')
		{
			i = parsdq(base, ++i);
			if (i == 0)
			{
				printf("quote non fermer\n");
				return ;
			}
		}
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_mini	base;
	int		i;

	(void)argc;
	(void)argv;
	i = 0;
	while (env[i])
		i++;
	base.env = malloc(sizeof(char *) * i + 1);
	if (!base.env)
		exit(EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		base.env[i] = ft_strdup(env[i]);
		i++;
	}
	while (1)
	{
		base.input = readline("Minirex >");
		parsing(base);
		if (base.input && base.input[0])
		{
			add_history(base.input);
			// base.mot = ft_split(base.input, ' ');
		}
	}
}
