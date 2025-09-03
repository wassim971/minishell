/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:52:14 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/03 21:09:49 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	len_list(t_mini_list *list)
{
	t_mini_list	*tmp;
	size_t		i;

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

static int	list_new_elem_str(t_mini_list **new, char *elem)
{
	(*new) = malloc(sizeof(t_mini_list));
	if (*new == NULL)
		return (0);
	(*new)->str = elem;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}
static void	add_first(t_mini_list **list, t_mini_list *new)
{
	(*list) = new;
	(*list)->prev = *list;
	(*list)->next = *list;
}

int	append(t_mini_list **list, char *elem)
{
	t_mini_list	*new;

	if (!list_new_elem_str(&new, elem))
		return (0);
	if (!(*list))
		add_first(list, new);
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
	{
		tmp = ft_strdup(s1);
		free(s1);
		return (tmp);
	}
	tmp = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (tmp);
}

t_cmd	*get_cmd(t_cmd *cmd, int state)
{
	static t_cmd	*save;

	if (!cmd && state == 0)
		return (save);
	save = cmd;
	return (NULL);
}
