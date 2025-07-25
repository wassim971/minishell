/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 00:37:17 by wbaali            #+#    #+#             */
/*   Updated: 2025/07/25 16:16:06 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_dollar_word(char *line, int size)
{
	char	*dollar;
	int		i;

	dollar = malloc(sizeof(char) * size);
	if (!dollar)
		return (NULL);
	i = 0;
	printf("%d\n", size);
	while (line[++i] && i < size)
	{
		dollar[i - 1] = line[i];
	}
	dollar[i - 1] = '\0';
	return (dollar);
}

char	*get_elem_env(t_mini_list *env, char *key)
{
	t_mini_list	*tmp;
	int			len;
	int			t;

	if (!key)
		return (NULL);
	tmp = env;
	len = len_list(tmp);
	t = ft_strlen(key);
	printf("%d,%d\n", len, t);
	while (len--)
	{
		if (ft_strncmp(tmp->str, key, t) == 0)
		{
			len = 0;
			while (tmp->str[len])
				if (tmp->str[len++] == '=')
					break ;
			return (ft_strdup(&(tmp->str[len])));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static int	in_env(t_data *data, char *line, int size, char **str)
{
	char	*tmp;
	char	*key;
	char	*value;

	key = get_dollar_word(line, size);
	printf("%s\n", key);
	value = get_elem_env(data->env, key);
	if (key)
		free(key);
	tmp = ft_strjoin(*str, value);
	if (value)
		free(value);
	free(*str);
	if (!tmp)
		return (0);
	*str = tmp;
	return (1);
}

static int	dollar_point_interrogation(t_data *data, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(data->exit_code);
	if (!tmp)
		return (0);
	// if (line != '$')
	tmp2 = ft_strjoin(tmp, *str);
	free(tmp);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	printf("%s\n", tmp2);
	return (1);
}

int	add_dollar(char *line, int *index, char **str, t_data *data)
{
	int	ctrl;
	int	n;
	int	start;

	n = *index;
	ctrl = exist_in_env(line, index, data);
	*index = n;
	if (ctrl == 1)
	{
		*index += ft_strlen_exp(line + n);
		return (in_env(data, &line[n], ft_strlen_exp(line + n), str));
	}
	else if (ctrl == 2)
	{
		(*index) += 2;
		printf("%c\n", line[n + 1]);
		return (dollar_point_interrogation(data, str));
	}
	else
	{
		start = *index;
		(*index)++;
		while (line[*index] && (ft_isalnum(line[*index])
				|| line[*index] == '_'))
			(*index)++;
		line[start] = '\0';
		return (1);
	}
}
