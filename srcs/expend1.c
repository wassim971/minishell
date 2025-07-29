/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:50:55 by wbaali            #+#    #+#             */
/*   Updated: 2025/07/25 19:01:41 by wbaali           ###   ########.fr       */
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
			*str = ft_strjoin(*str, "$");
			(*index)++;
		}
		return (1);
	}
	char_to_str[0] = *c;
	char_to_str[1] = '\0';
	(*index)++;
	tmp2 = ft_strjoin(*str, char_to_str);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}
