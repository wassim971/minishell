/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:27:58 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/12 16:18:01 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	count_arg(char **params)
{
	int	count;

	count = 0;
	while (params[count])
		count++;
	return (count);
}

static void	error_malloc(void)
{
	print_error(MALLOC_ERROR);
	return ;
}

static void	update_oldpwd(t_data *data)
{
	t_mini_list	*tmp;
	char		*test;
	int			len;

	tmp = data->env;
	test = NULL;
	len = len_list(tmp);
	while (len--)
	{
		if (ft_strncmp(tmp->str, "PWD=", 3) == 0)
			test = tmp->str;
		tmp = tmp->next;
	}
	if (!test)
		export("OLDPWD", &data->env);
	if (test)
	{
		test = ft_strjoin("OLD", test);
		if (!test)
			return (error_malloc());
		export(test, &data->env);
	}
	free(test);
}

void	update_pwd(t_data *data, char *param)
{
	char	cwd[PATH_MAX];
	char	*pwd;

	update_oldpwd(data);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		perror(param);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (error_malloc());
	export(pwd, &data->env);
	free(pwd);
}

int	ft_cd(t_data *data, char **params)
{
	int		res;
	char	*home;
	int		i;

	i = 1;
	if (count_arg(params) == 1)
	{
		home = get_env_value("HOME", data->env, data);
		if (!home)
		{
			print_error("cd: HOME not set\n");
			return (1);
		}
		res = chdir(home);
		i = ft_cd_part(res, data, "cd");
	}
	else if (count_arg(params) == 2)
	{
		res = chdir(params[1]);
		i = ft_cd_part(res, data, params[1]);
	}
	return (i);
}
