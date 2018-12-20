/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:43:25 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/26 16:48:21 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		index;
	char	chr;

	index = ft_strlen(s);
	chr = (char)c;
	while (index >= 0)
	{
		if (s[index] == chr)
			break ;
		index--;
	}
	if (index >= 0)
		return ((char *)&s[index]);
	else
		return (NULL);
}
