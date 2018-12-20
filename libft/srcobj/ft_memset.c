/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:59:51 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/26 18:22:10 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pen;

	pen = (unsigned char *)b;
	while (len > 0)
	{
		*pen = (unsigned char)c;
		pen++;
		len--;
	}
	return (b);
}
