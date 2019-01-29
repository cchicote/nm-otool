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

t_symbol					*new_symbol(void)
{
	t_symbol				*new;

	new = (t_symbol*)ft_memalloc(sizeof(t_symbol));
	ft_bzero(new, sizeof(t_symbol));
	return (new);
}

int							check_stab_32(void *content, uint32_t i, struct symtab_command *sc, int need_swap)
{
	struct nlist			*array;

	array = (void*)content + swap_endian(sc->symoff, need_swap);
	if (N_STAB & swap_endian(array[i].n_type, need_swap))
		return (TRUE);
	return (FALSE);
}
int							check_stab_64(void *content, uint32_t i, struct symtab_command *sc, int need_swap)
{
	struct nlist_64			*array;

	array = (void*)content + swap_endian(sc->symoff, need_swap);
	if (N_STAB & swap_endian(array[i].n_type, need_swap))
		return (TRUE);
	return (FALSE);
}

void					sort_symbols_by_name(t_symbol **sym_head)
{
	t_symbol			*iterator;
	t_symbol			*tmp_previous;
	t_symbol			*tmp;
	t_symbol			*tmp_next;
	
	iterator = *sym_head;
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
				*sym_head = tmp_next;
			tmp->next = tmp_next->next;
			tmp_next->next = tmp;
			iterator = *sym_head;
			tmp_previous = NULL;
		}
		else
		{
			tmp_previous = iterator;
			iterator = iterator->next;
		}
	}
}