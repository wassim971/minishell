/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 01:13:43 by wbaali            #+#    #+#             */
/*   Updated: 2025/07/18 08:32:55 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	print_error_token(t_token *token, t_data *data)
{
	write(2, "syntax error near unexpected token ", 35);
	write(2, "'", 1);
	if (token->next == data->token)
		write(2, "newline", 7);
	else
		write(2, token->next->str, ft_strlen(token->next->str));
	write(2, "'\n", 2);
	return (false);
}

bool	print_error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	return (true);
}

// void	print_token(t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp->next != token)
// 	{
// 		printf("Type : %d, [%s]\n", tmp->type, tmp->str);
// 		tmp = tmp->next;
// 	}
// 	printf("Type : %d, [%s]\n", tmp->type, tmp->str);
// }

void	set_types(t_token **tmp, int i)
{
	if (i == INPUT)
		(*tmp)->types = "Input";
	if (i == HEREDOC)
		(*tmp)->types = "HEREDOC";
	if (i == TRUNC)
		(*tmp)->types = "TRUNC";
	if (i == APPEND)
		(*tmp)->types = "APPEND";
	if (i == PIPE)
		(*tmp)->types = "PIPE";
	if (i == CMD)
		(*tmp)->types = "CMD";
	if (i == ARG)
		(*tmp)->types = "ARG";
}

void	print_token(t_token *token)
{
	t_token	*tmp;

	if (!token)
	{
		printf("Token list is empty.\n");
		return ;
	}
	tmp = token;
	while (tmp->next && tmp->next != token)
	{
		set_types(&tmp, tmp->type);
		printf("Type : %s, [%s]\n", tmp->types, tmp->str);
		tmp = tmp->next;
	}
	set_types(&tmp, tmp->type);
	printf("Type : %s, [%s]\n", tmp->types, tmp->str);
}
