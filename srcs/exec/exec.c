/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 13:19:29 by wbaali            #+#    #+#             */
/*   Updated: 2025/08/04 18:02:30 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strncmp("echo", cmd, INT_MAX) || !ft_strncmp("cd", cmd, INT_MAX) ||
		!ft_strncmp("pwd", cmd, INT_MAX) || !ft_strncmp("export", cmd, INT_MAX) ||
		!ft_strncmp("unset", cmd, INT_MAX) || !ft_strncmp("env", cmd, INT_MAX) ||
		!ft_strncmp("exit", cmd, INT_MAX))
		return (true);
	return (false);
}

/*exec(t_data *data) {
  t_cmd	*tmp;

  tmp = data->cmd;
}*/
