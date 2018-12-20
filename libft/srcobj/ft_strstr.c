/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:21:53 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/26 19:39:57 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int index1;
	int	index2;
	int debut;

	index1 = 0;
	debut = 0;
	if (s2[0] == '\0')
		return ((char *)(s1));
	while (s1[index1] != '\0')
	{
		index2 = 0;
		debut = index1;
		if (s1[index1] == s2[index2])
		{
			while (s1[index1] == s2[index2] && s2[index2] != '\0')
			{
				index1++;
				index2++;
			}
			if (s2[index2] == '\0')
				return ((char *)(s1 + debut));
		}
		index1 = (debut + 1);
	}
	return (NULL);
}
