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
	char					*str_value;

	str_value = ft_llutoa_base(addr, 16);
	print_char_filled(str_value, '0', size);
	ft_putchar('\t');
	free(str_value);
}

void						print_hex_num(uint32_t value)
{
	char					*str_value;

	str_value = ft_llutoa_base(value, 16);
	print_char_filled(str_value, '0', 8);
	ft_putchar(' ');
	free(str_value);
}

void						print_hex_char(char value)
{
	char					*tmp;
	char					*converted;

	converted = ft_llutoa_base(value, 16);
	tmp = fill_with_char(converted, '0', 16);
	ft_putchar(tmp[14]);
	ft_putchar(tmp[15]);
	ft_putchar(' ');
	free(converted);
	free(tmp);
}
