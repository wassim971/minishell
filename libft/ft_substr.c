/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:55:32 by wbaali            #+#    #+#             */
/*   Updated: 2024/11/18 12:11:53 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	cpy(char *new, char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
	{
		new = malloc(1);
		if (!new)
			return (NULL);
		return (new[0] = '\0', new);
	}
	if (start + len > str_len)
		len = str_len - start;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	cpy(new, s, start, len);
	return (new);
}
