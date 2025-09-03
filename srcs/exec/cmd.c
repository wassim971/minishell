/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:05:05 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/03 20:56:29 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	cmd_new_elem(t_cmd **new, int infile, int outfile, char **cmd_param)
{
	(*new) = malloc(sizeof(t_cmd));
	if (*new == NULL)
		return (0);
	(*new)->skip_cmd = false;
	(*new)->infile = infile;
	(*new)->outfile = outfile;
	(*new)->cmd_param = cmd_param;
	(*new)->pid = 0;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

int	append_cmd(t_cmd **list, int infile, int outfile, char **cmd_param)
{
	t_cmd	*new;

	if (!cmd_new_elem(&new, infile, outfile, cmd_param))
		return (0);
	if (!(*list))
	{
		(*list) = new;
		(*list)->prev = *list;
		(*list)->next = *list;
	}
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}
