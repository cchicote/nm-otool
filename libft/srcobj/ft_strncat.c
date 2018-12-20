/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:12:25 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/29 21:50:49 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	index;
	int		findest;

	index = 0;
	findest = ft_strlen(dest);
	while (src[index] != '\0' && index < n)
	{
		dest[findest] = src[index];
		findest++;
		index++;
	}
	dest[findest] = '\0';
	return (dest);
}
