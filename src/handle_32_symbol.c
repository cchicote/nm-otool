/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32_symbol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 00:14:48 by cchicote          #+#    #+#             */
/*   Updated: 2019/01/26 00:14:54 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						get_symbol_type_char_32(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol)
{
	struct nlist			*array;
	uint8_t					n_type_value;

	array = file->content + sc->symoff;
	symbol->section_index = array[i].n_sect;
	n_type_value = (array[i].n_type & N_TYPE);
	if (n_type_value == N_ABS)
		symbol->type_char = 'a';
	else if (n_type_value == N_UNDF && array[i].n_value)
		symbol->type_char = 'c';
	else if (n_type_value == N_INDR)
		symbol->type_char = 'i';
	else if ((n_type_value == N_UNDF && !array[i].n_value) ||
		n_type_value == N_PBUD)
		symbol->type_char = 'u';
	else if (array[i].n_desc & N_WEAK_REF)
		symbol->type_char = 'W';
	else if (n_type_value == N_SECT && !symbol->type_char)
		symbol->type_char = '?';
	if (N_EXT & array[i].n_type)
		symbol->is_external = TRUE;
}

void						get_symbol_name_32(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol)
{
	char					*stringtable;
	struct nlist			*array;

	array = file->content + sc->symoff;
	stringtable = file->content + sc->stroff;
	symbol->name = stringtable + array[i].n_un.n_strx;
}

void						get_symbol_value_32(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol)
{
	struct nlist			*array;
	uint8_t					n_type_value;

	array = file->content + sc->symoff;
	if ((n_type_value = array[i].n_type & N_TYPE))
		symbol->value = array[i].n_value;
}

void						parse_symtable_32(t_file *file, struct symtab_command *sc, t_arch *arch)
{
	uint32_t				i;
	t_symbol				*symbol;

	i = -1;
	if (file->is_little_endian)
		swap_nlist_32(file, sc->symoff);
	while (++i < sc->nsyms)
	{
		if (check_stab_32(file, i, sc))
			continue;
		symbol = new_symbol();	
		get_symbol_name_32(file, i, sc, symbol);
		get_symbol_value_32(file, i, sc, symbol);
		get_symbol_type_char_32(file, i, sc, symbol);
		add_symbol_to_list(&arch->sym_head, symbol);
	}
}
