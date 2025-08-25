/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 14:33:38 by wbaali            #+#    #+#             */
/*   Updated: 2025/08/22 15:54:10 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	len_cmd(t_cmd *list)
{
	t_cmd	*tmp;
	size_t	i;

	if ((list))
	{
		tmp = list;
		i = 1;
		while (tmp->next != list)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

void	absolute_path(char **path, char *cmd, t_data *data)
{
	*path = ft_strdup(cmd);
	if (!(*path))
		free_all(data, MALLOC_ERROR, EXT_MALLOC);
	if (access((*path), F_OK))
	{
		write(2, (*path), ft_strlen((*path)));
		write(2, " : command not found\n", 21);
		free(*path);
		*path = NULL;
	}
}

char	**lst_to_arr(t_mini_list *env)
{
	t_mini_list	*lst;
	char		**dest;
	int			i;

	dest = NULL;
	i = 0;
	lst = env;
	dest = (char **)malloc(sizeof(char *) * (len_list(lst) + 1));
	if (!dest)
		return (NULL);
	dest[i] = (lst->str);
	lst = lst->next;
	i++;
	while (lst != env)
	{
		dest[i] = (lst->str);
		lst = lst->next;
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

void	signals2(void)
{
	signal(SIGQUIT, SIG_DFL);
}
