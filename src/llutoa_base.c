/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llutoa_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:55:29 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/21 19:55:35 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						print_char_filled(char *src, char to_fill, int size)
{
	char					*ret;

	ret = fill_with_char(src, to_fill, size);
	ft_putstr(ret);
	free(ret);
}

char						*fill_with_char(char *src, char to_fill, int size)
{
	char					*ret;
	int						i;
	int						cap;

	ret = ft_memalloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = '\0';
	i = -1;
	cap = size - ft_strlen(src);
	while (++i < size)
	{
		if (i >= cap)
			ret[i] = *src++;
		else
			ret[i] = to_fill;
	}
	return (ret);
}

size_t						get_number_len(uint64_t nb, int base)
{
	size_t 					len;

	len = 0;
	while (nb > 0)
	{
		nb /= base;
		len++;
	}
	return (len);
}

char						*ft_llutoa_base(uint64_t nb, int base)
{
	size_t					len;
	uint64_t				ret;
	char					*str;

	if (nb <= 0)
		return (ft_strdup("0"));
	len = get_number_len(nb, base);
	str = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		ret = (nb % base) + '0';
		if (base > 10 && ret > '9')
			str[len - 1] = (nb % base) - 10 + 'a';
		else
			str[len - 1] = ret;
		nb /= base;
		len--;
	}
	return (str);
}