/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:50:34 by wbaali            #+#    #+#             */
/*   Updated: 2024/11/13 12:53:57 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	value;

	d = (unsigned char *)s;
	value = (unsigned char)c;
	while (n--)
	{
		if (*d == value)
			return ((void *)d);
		d++;
	}
	return (NULL);
}
