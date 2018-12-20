/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:46:13 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/26 16:46:09 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *pen;

	pen = (unsigned char *)s;
	while (n > 0)
	{
		if (*pen == (unsigned char)c)
			return (pen);
		pen++;
		n--;
	}
	return (NULL);
}
