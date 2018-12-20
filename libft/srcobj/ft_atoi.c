/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:26:10 by cchicote          #+#    #+#             */
/*   Updated: 2015/11/26 19:34:29 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_atoi(const char *src)
{
	int	nbr;
	int	index;
	int	neg;

	nbr = 0;
	neg = 0;
	index = 0;
	while (src[index] == ' ' || src[index] == '\t' || src[index] == '\n'
			|| src[index] == '\r' || src[index] == '\v' || src[index] == '\f')
		index++;
	if (src[index] == '-')
		neg = 1;
	if (src[index] == '+' || src[index] == '-')
		index++;
	while (src[index] != '\0' && src[index] >= '0' && src[index] <= '9')
	{
		nbr *= 10;
		nbr += (int)src[index] - '0';
		index++;
	}
	if (neg == 1)
		return (-nbr);
	else
		return (nbr);
}
