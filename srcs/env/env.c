/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:46:36 by wbaali            #+#    #+#             */
/*   Updated: 2025/08/26 11:33:03 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <limits.h> // pour PATH_MAX
#include <unistd.h> // pour getcwd

bool	make_env2(t_data *data)
{
	char	path[PATH_MAX];
	char	*tmp;

	tmp = ft_strdup("OLDPWD");
	if (!tmp || !append(&(data->env), tmp) || getcwd(path, PATH_MAX) == NULL)
		free_all(data, MALLOC_ERROR, EXT_MALLOC);
	tmp = ft_strjoin("PWD=", path);
	if (!tmp || !append(&(data->env), tmp))
		free_all(data, MALLOC_ERROR, EXT_MALLOC);
	tmp = ft_strdup("SHLVL=1");
	if (!tmp || !append(&(data->env), tmp))
		free_all(data, MALLOC_ERROR, EXT_MALLOC);
	tmp = ft_strdup("_=/usr/bin/env");
	if (!tmp || !append(&(data->env), tmp))
		free_all(data, MALLOC_ERROR, EXT_MALLOC);
	return (1);
}

int	make_env(t_data *data, char **env)
{
	t_mini_list	*list;
	int			i;
	char		*tmp;

	if (!(*env))
		return (make_env2(data));
	i = -1;
	list = NULL;
	while (env[++i])
	{
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return (free_list(&list));
		if (!append(&list, tmp))
			return (free_list(&list));
	}
	data->env = list;
	return (1);
}
