/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_symbol.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 23:53:13 by cchicote          #+#    #+#             */
/*   Updated: 2019/01/25 23:53:20 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							check_stab_64(struct nlist_64 array)
{
	if (N_STAB & array.n_type)
		return (TRUE);
	return (FALSE);
}

void						get_symbol_type_char_64(t_symbol *symbol, struct nlist_64 array)
{
	uint8_t					n_type_value;

	symbol->section_index = array.n_sect;
	n_type_value = (array.n_type & N_TYPE);
	if (n_type_value == N_ABS)
		symbol->type_char = 'a';
	else if (n_type_value == N_UNDF && array.n_value)
	{
		symbol->value = array.n_value;
		symbol->type_char = 'c';
	}
	else if (n_type_value == N_INDR)
		symbol->type_char = 'i';
	else if ((n_type_value == N_UNDF && !array.n_value) ||
		n_type_value == N_PBUD)
		symbol->type_char = 'u';
	else if (array.n_desc & N_WEAK_REF)
		symbol->type_char = 'W';
	else if (n_type_value == N_SECT && !symbol->type_char)
		symbol->type_char = '?';
	if (N_EXT & array.n_type)
		symbol->is_external = TRUE;
}

void						get_symbol_value_64(t_symbol *symbol, struct nlist_64 array)
{
	if (array.n_type & N_TYPE)
		symbol->value = array.n_value;
}

void						get_symbol_name_64(t_file *file, t_symbol *symbol, struct nlist_64 array, char *stringtable)
{
	symbol->name = (void*)(stringtable + array.n_un.n_strx) > (file->content + file->len) 
		? NULL : stringtable + array.n_un.n_strx;
}

void						parse_symtable_64(t_file *file, struct symtab_command *sc, t_arch *arch)
{
	uint32_t				i;
	t_symbol				*symbol;

	i = -1;

	while (++i < sc->nsyms)
	{
		if (arch->is_little_endian)
			swap_nlist_64(file, arch, sc->symoff, i);
		if (check_stab_64(((struct nlist_64*)(file->content + arch->offset + sc->symoff))[i]))
			continue;
		symbol = new_symbol();
		get_symbol_name_64(file, symbol, ((struct nlist_64*)(file->content + arch->offset + sc->symoff))[i], (char*)(file->content + arch->offset + sc->stroff));
		get_symbol_value_64(symbol, ((struct nlist_64*)(file->content + arch->offset + sc->symoff))[i]);
		get_symbol_type_char_64(symbol, ((struct nlist_64*)(file->content + arch->offset + sc->symoff))[i]);
		add_symbol_to_list(&arch->sym_head, symbol);
	}
}
