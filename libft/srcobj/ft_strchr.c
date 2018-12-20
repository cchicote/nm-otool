/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 15:31:29 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/26 20:52:03 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		index;
	int		occ;
	char	chr;

	chr = (char)c;
	index = 0;
	occ = 0;
	if (chr == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[index] != '\0')
	{
		if (s[index] == chr)
		{
			occ++;
			break ;
		}
		index++;
	}
	if (occ > 0)
		return ((char *)&s[index]);
	else
		return (NULL);
}
