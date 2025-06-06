/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:54:44 by wbaali            #+#    #+#             */
/*   Updated: 2025/04/19 15:06:38 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	in_charset(char s, char c)
{
	if (s == c)
		return (1);
	return (0);
}

void	ft_free_split(char **splitted)
{
	unsigned int	i;

	i = 0;
	while (splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

unsigned int	count_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	words;
	unsigned int	in;

	i = 0;
	words = 0;
	in = 0;
	while (s[i] && in_charset(s[i], c))
		i++;
	while (s[i])
	{
		if (!in_charset(s[i], c) && !in)
		{
			in = 1;
			words++;
		}
		else if (in_charset(s[i], c) && in)
			in = 0;
		i++;
	}
	return (words);
}

char	*write_word(char const *s, char c)
{
	unsigned int	i;
	unsigned int	size;
	char			*word;

	size = 0;
	while (s[size] && !in_charset(s[size], c))
		size++;
	if (size == 0)
		return (NULL);
	word = malloc(sizeof(char) * (size + 1));
	if (word)
	{
		i = 0;
		while (i < size)
		{
			word[i] = s[i];
			i++;
		}
		word[i] = '\0';
	}
	return (word);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	words;
	unsigned int	i;
	unsigned int	word;
	char			**splitted;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	splitted = malloc(sizeof(char *) * (words + 1));
	if (!splitted)
		return (NULL);
	splitted[words] = 0;
	i = 0;
	word = 0;
	while (s[i] && word < words)
	{
		while (s[i] && in_charset(s[i], c))
			i++;
		splitted[word] = write_word(s + i, c);
		if (!splitted[word])
			return (ft_free_split(splitted), NULL);
		i += ft_strlen(splitted[word]);
		word++;
	}
	return (splitted);
}
