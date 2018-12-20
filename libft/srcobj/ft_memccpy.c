/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:12:07 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/26 16:45:42 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char *pen;
	unsigned char *s;

	pen = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n > 0)
	{
		if ((*pen = *s) == (unsigned char)c)
			return (pen + 1);
		*pen = *s;
		pen++;
		s++;
		n--;
	}
	return (NULL);
}
