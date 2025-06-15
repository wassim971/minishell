/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:33 by wbaali            #+#    #+#             */
/*   Updated: 2025/06/15 15:45:39 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int	chercher_fin(const char *texte, const char *motif)
{
	char	*position;

	position = strstr(texte, motif);
	if (position != NULL)
	{
		return ((int)(position - texte) + ft_strlen(motif) - 1);
	}
	else
	{
		return (-1);
	}
}

void	replace(t_mini *base, int start, int end, char *expend)
{
	char	*new_input;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_input = malloc(sizeof(char) * (ft_strlen(base->input) - (end - start
					- 1) + ft_strlen(expend)));
	while (i != start - 1)
	{
		new_input[i] = base->input[i];
		i++;
	}
	while (expend && expend[j] != '\0')
	{
		new_input[i] = expend[j];
		i++;
		j++;
	}
	base->index = i;
	j = end;
	while (base->input[j])
	{
		new_input[i] = base->input[j];
		i++;
		j++;
	}
	new_input[i] = '\0';
	free(base->input);
	base->input = new_input;
}

char	*get_exp(char *cmd, t_mini base, int len)
{
	char	*expend;
	int		i;

	i = 0;
	while (base.env[i] && ft_strnstr(base.env[i], cmd, len) == 0)
		i++;
	if (!base.env[i])
		return (NULL);
	expend = ft_strdup(base.env[i] + (len + 1));
	free(cmd);
	return (expend);
}

char	*ft_strndup_range(const char *s, int start, int end)
{
	int		len;
	char	*sub;
	int		i;

	if (!s || start < 0 || end < start)
		return (NULL);
	len = end - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (start < end && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

int	parsexp(t_mini *base, int i)
{
	int		start;
	char	*expend;

	start = i;
	if (base->input[i] == '\'')
		return (0);
	while (ft_isalnum(base->input[i]) || base->input[i] == '_')
		i++;
	if (start != i)
	{
		expend = ft_strndup_range(base->input, start, i);
		expend = get_exp(expend, *base, (i - start));
		replace(base, start, i, expend);
		i = base->index - 1;
	}
	return (i);
}

int	parsdq(t_mini *base, int i)
{
	while (base->input[i] && base->input[i] != '"')
	{
		if (base->input[i] == '$')
			i = parsexp(base, ++i);
		i++;
	}
	if (base->input[i] == '\0')
		return (0);
	return (i);
}

void	parsing(t_mini *base)
{
	int	i;

	i = 0;
	while (base->input[i])
	{
		if (base->input[i] == '"')
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
		if (base.input && base.input[0])
		{
			add_history(base.input);
			// base.mot = ft_split(base.input, ' ');
		}
		parsing(&base);
	}
}
