/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:42:45 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/26 20:41:04 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t index;
	size_t nb;

	index = 0;
	nb = 0;
	while (s1[index] != '\0' && s2[index] != '\0' && s1[index] == s2[index]
			&& (index < n))
	{
		index++;
		nb++;
	}
	if (nb == index && n == index)
		return (0);
	else
		return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
