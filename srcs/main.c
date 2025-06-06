/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:04:33 by wbaali            #+#    #+#             */
/*   Updated: 2025/06/06 15:21:58 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsexp(t_mini base, int i)
{
}

int	parsdq(t_mini base, int i)
{
	while (base.input[i] && base.input[i] != '"')
	{
		if (base.input[i] == '$')
			parsexp(base, i);
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
