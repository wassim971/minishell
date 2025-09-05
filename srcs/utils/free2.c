/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 13:58:32 by wbaali            #+#    #+#             */
/*   Updated: 2025/09/05 14:56:38 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	if (arr)
		free(arr);
	arr = NULL;
}

void	free_part(t_data *data)
{
	if (data->cmd)
		free_cmd(&data->cmd);
	if (data->token)
		free_token(&data->token);
}
