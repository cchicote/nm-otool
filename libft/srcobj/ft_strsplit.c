/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 17:47:04 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/29 20:03:20 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	int		ft_nbmots(char const *s, char c)
{
	int index;
	int	nbmots;

	index = 0;
	nbmots = 0;
	while (s[index] != '\0')
	{
		if (s[index] != c && s[index + 1] == c)
			nbmots++;
		else if (s[index] != c && s[index + 1] == '\0')
			nbmots++;
		index++;
	}
	return (nbmots);
}

char			**ft_strsplit(char const *s, char c)
{
	int		start;
	char	**tab;
	int		index;
	int		i;

	index = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	tab = (char **)malloc(sizeof(char *) * (ft_nbmots(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	tab[ft_nbmots(s, c)] = NULL;
	while (i < ft_nbmots(s, c))
	{
		while (s[index] == c)
			index++;
		start = index;
		while (s[index] != c)
			index++;
		tab[i] = ft_strsub(s, (unsigned int)start, ((size_t)(index - start)));
		i++;
	}
	return (tab);
}
