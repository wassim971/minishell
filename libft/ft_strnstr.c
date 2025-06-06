/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wbaali <wbaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:33:50 by wbaali            #+#    #+#             */
/*   Updated: 2025/04/30 10:49:59 by wbaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needlelen;

	if (!haystack)
		return (NULL);
	needlelen = ft_strlen(needle);
	if (!needle)
		return ((char *)haystack);
	while (*haystack && len > needlelen && ft_strncmp(haystack, needle,
			needlelen))
	{
		haystack++;
		len--;
	}
	if (len >= needlelen && !ft_strncmp(haystack, needle, needlelen))
		return ((char *)haystack);
	return (NULL);
}
