/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marapovi <marapovi@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:32:01 by marapovi          #+#    #+#             */
/*   Updated: 2026/08/08 14:46:10 by marapovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	len++;
	ptr = (char *)ft_calloc(len, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (i < len - 1)
	{
		ptr[i] = s[i];
		i++;
	}
	return (ptr);
}
