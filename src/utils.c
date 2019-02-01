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

void						add_symbol_to_list(t_symbol **sym_head, t_symbol *symbol)
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

void						swap_nlist_32(t_file *file, uint32_t offset)
{
	struct nlist			*nlist;

	nlist = (struct nlist*)file->content + offset;
	SWAP(nlist->n_un.n_strx);
	SWAP(nlist->n_type);
	SWAP(nlist->n_sect);
	SWAP(nlist->n_desc);
	SWAP(nlist->n_value);
}

void						swap_nlist_64(t_file *file, uint32_t offset)
{
	struct nlist_64			*nlist_64;

	nlist_64 = (struct nlist_64*)file->content + offset;
	SWAP(nlist_64->n_un.n_strx);
	SWAP(nlist_64->n_type);
	SWAP(nlist_64->n_sect);
	SWAP(nlist_64->n_desc);
	SWAP(nlist_64->n_value);
}

void					sort_arch_symbols(t_file *file)
{
	t_arch				*tmp;

	tmp = file->arch;
	if (!file->is_fat)
	{
		sort_symbols_by_name(tmp);
		return ;
	}
	while (tmp)
	{
		sort_symbols_by_name(tmp);
		tmp = tmp->next;
	}
}

void					sort_symbols_by_name(t_arch *arch)
{
	t_symbol			*iterator;
	t_symbol			*tmp_previous;
	t_symbol			*tmp;
	t_symbol			*tmp_next;
	
	iterator = arch->sym_head;
	tmp_previous = NULL;
	while (iterator)
	{
		if (iterator->next && ft_strcmp(iterator->name, iterator->next->name) > 0)
		{
			tmp = iterator;
			tmp_next = iterator->next;
			if (tmp_previous)
				tmp_previous->next = tmp_next;
			else
				arch->sym_head = tmp_next;
			tmp->next = tmp_next->next;
			tmp_next->next = tmp;
			iterator = arch->sym_head;
			tmp_previous = NULL;
		}
		else
		{
			tmp_previous = iterator;
			iterator = iterator->next;
		}
	}
}