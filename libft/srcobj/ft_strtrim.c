/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 20:24:56 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/29 17:15:30 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s)
{
	int		index;
	int		start;
	int		end;

	index = 0;
	if (s == NULL)
		return (NULL);
	while ((s[index]) && (s[index] == ' ' || s[index] == '\t'
				|| s[index] == '\n'))
		index++;
	start = index;
	if (s[index] == '\0')
		return (ft_strsub(s, (unsigned int)start, 0));
	while (s[index] != '\0')
	{
		if (s[index] != ' ' && s[index] != '\t' && s[index] != '\n')
			end = index;
		index++;
	}
	return (ft_strsub(s, (unsigned int)start, (size_t)end - (size_t)start + 1));
}
