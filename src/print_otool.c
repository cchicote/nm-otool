/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_otool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 21:28:05 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/21 21:28:13 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						print_otool_address(uint64_t addr, int size)
{
	ft_putstr(fill_with_char(ft_llutoa_base(addr, 16), '0', size));
	ft_putchar('\t');
}

void						print_hex_num(uint32_t value)
{
	ft_putstr(fill_with_char(ft_llutoa_base(value, 16), '0', 8));
	ft_putchar(' ');
}

void						print_hex_char(char value)
{
	char					*tmp;

	tmp = fill_with_char(ft_llutoa_base(value, 16), '0', 16);
	ft_putchar(tmp[14]);
	ft_putchar(tmp[15]);
	ft_putchar(' ');
	free(tmp);
}
