/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:50:55 by wbaali            #+#    #+#             */
/*   Updated: 2025/07/30 01:00:21 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	add_char(char *c, char **str, t_data *data, int *index)
{
	char	char_to_str[2];
	char	*tmp2;
	int		i;

	i = 0;
	if (c[i] == '$' && !data->sq && exist_in_env(c, &i, data))
	{
		if (i == 0)
		{
			ft_strjoin_free(*str, "$");
			(*index)++;
		}
		return (1);
	}
	char_to_str[0] = *c;
	char_to_str[1] = '\0';
	(*index)++;
	tmp2 = ft_strjoin_free(*str, char_to_str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}
