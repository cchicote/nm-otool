/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:51:58 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/29 21:50:40 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int index;
	int findest;

	index = 0;
	findest = ft_strlen(dest);
	while (src[index] != '\0')
	{
		dest[findest] = src[index];
		findest++;
		index++;
	}
	dest[findest] = '\0';
	return (dest);
}
