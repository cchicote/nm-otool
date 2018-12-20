/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 21:43:41 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/29 22:33:25 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	index;
	size_t	index2;
	int		acopier;
	size_t	renvoi;

	index = 0;
	index2 = 0;
	renvoi = (ft_strlen(src) + ft_strlen(dst));
	acopier = (size - (ft_strlen(dst)) - 1);
	if (size < ft_strlen(dst))
		return (size + ft_strlen(src));
	while (index < ft_strlen(dst))
		index++;
	while (acopier > 0)
	{
		dst[index] = src[index2];
		index++;
		index2++;
		acopier--;
	}
	dst[index] = '\0';
	return (renvoi);
}
