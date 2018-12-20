/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:02:57 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/26 16:45:31 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *pen;
	unsigned char *s;

	pen = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (n > 0)
	{
		*pen = *s;
		pen++;
		s++;
		n--;
	}
	return (dst);
}
