/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:48:01 by wbaali            #+#    #+#             */
/*   Updated: 2024/11/15 17:56:50 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;

	if (size != 0 && nmemb > ((size_t)-1 / size))
	{
		return (NULL);
	}
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
	{
		free(ptr);
		return (NULL);
	}
	i = 0;
	while (i < (nmemb * size))
	{
		*(unsigned char *)(ptr + i) = 0;
		i++;
	}
	return (ptr);
}
