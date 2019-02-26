/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:31:11 by cchicote          #+#    #+#             */
/*   Updated: 2019/01/25 15:31:18 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						add_arch_to_list(t_file *file, t_arch *arch)
{
	t_arch					*tmp;

	tmp = file->arch;
	arch->next = NULL;
	if (!tmp)
	{
		file->arch = arch;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = arch;
}

t_symbol					*new_symbol(void)
{
	t_symbol				*new;

	new = (t_symbol*)ft_memalloc(sizeof(t_symbol));
	ft_bzero(new, sizeof(t_symbol));
	return (new);
}

void						add_symbol_to_list(t_symbol **sym_head,
								t_symbol *symbol)
{
	t_symbol				*tmp;

	tmp = *sym_head;
	symbol->next = NULL;
	if (!tmp)
	{
		*sym_head = symbol;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = symbol;
}
