/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 15:38:06 by wbaali            #+#    #+#             */
/*   Updated: 2025/08/22 15:55:15 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_mini_list *env)
{
	t_mini_list	*temp;

	temp = env;
	if (!temp)
		return (0);
	if (ft_strchr(temp->str, '='))
		printf("%s\n", temp->str);
	temp = temp->next;
	while (temp != env)
	{
		if (ft_strchr(temp->str, '='))
			printf("%s\n", temp->str);
		temp = temp->next;
	}
	return (0);
}
