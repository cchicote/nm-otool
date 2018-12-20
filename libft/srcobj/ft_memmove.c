/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:38:33 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/30 20:32:10 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*pen;
	unsigned char	*s;
	size_t			index;

	pen = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (dst >= src && dst < (len + src))
	{
		index = len;
		while (index > 0)
		{
			pen[index - 1] = s[index - 1];
			index--;
		}
	}
	else
	{
		index = 0;
		while (index < len)
		{
			pen[index] = s[index];
			index++;
		}
	}
	return (dst);
}
