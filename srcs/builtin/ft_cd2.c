/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 15:42:39 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/12 16:14:25 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env_value(char *key, t_mini_list *env, t_data *data)
{
	int		len;
	char	*value;

	len = ft_strlen(key);
	if (ft_strncmp(env->str, key, len) == 0 && env->str[len] == '=')
	{
		value = env->str + len + 1;
		return (value);
	}
	env = env->next;
	while (env != data->env)
	{
		if (ft_strncmp(env->str, key, len) == 0 && env->str[len] == '=')
		{
			value = env->str + len + 1;
			return (value);
		}
		env = env->next;
	}
	return (NULL);
}

int	ft_cd_part(int res, t_data *data, char *params)
{
	if (res == 0)
	{
		update_pwd(data, params);
		return (0);
	}
	else
		perror(params);
	return (1);
}
