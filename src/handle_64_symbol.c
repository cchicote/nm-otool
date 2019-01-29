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

char						get_char_by_section_64(void *content, uint32_t n_sect, int need_swap)
{
	struct section_64		*sect;
	char					type_char;
	
	type_char = 's';
	if (n_sect == 0 || (sect = handle_64_header(NULL, content, n_sect, need_swap)) == NULL)
		return (type_char);
	if (ft_strncmp(sect->segname, SEG_TEXT, 16) == 0
		&& ft_strncmp(sect->sectname, SECT_TEXT, 16) == 0)
		type_char = 't';
	else if (ft_strncmp(sect->segname, SEG_DATA, 16) == 0
		&& ft_strncmp(sect->sectname, SECT_DATA, 16) == 0)
		type_char = 'd';
	else if (ft_strncmp(sect->segname, SEG_DATA, 16) == 0
		&& ft_strncmp(sect->sectname, SECT_BSS, 16) == 0)
		type_char = 'b';
	return (type_char);
}

void						get_symbol_type_char_64(void *content, uint32_t i, struct symtab_command *sc, t_symbol *symbol, int need_swap)
{
	struct nlist_64			*array;
	uint8_t					n_type_value;

	array = (void*)content + swap_endian(sc->symoff, need_swap);
	symbol->type_char = get_char_by_section_64(content, swap_endian(array[i].n_sect, need_swap), need_swap);
	n_type_value = (swap_endian(array[i].n_type, need_swap) & N_TYPE);
	if (n_type_value == N_ABS)
		symbol->type_char = 'a';
	else if (n_type_value == N_UNDF && swap_endian(array[i].n_value, need_swap))
		symbol->type_char = 'c';
	else if (n_type_value == N_INDR)
		symbol->type_char = 'i';
	else if ((n_type_value == N_UNDF && !swap_endian(array[i].n_value, need_swap)) ||
		n_type_value == N_PBUD)
		symbol->type_char = 'u';
	else if (array[i].n_desc & N_WEAK_REF)
		symbol->type_char = 'W';
	else if (n_type_value == N_SECT && !symbol->type_char)
		symbol->type_char = '?';
	if (N_EXT & array[i].n_type)
		symbol->type_char  = ft_toupper(symbol->type_char);
}

void						get_symbol_name_64(void *content, uint32_t i, struct symtab_command *sc, t_symbol *symbol, int need_swap)
{
	char					*stringtable;
	struct nlist_64			*array;

	array = (void*)content + swap_endian(sc->symoff, need_swap);
	stringtable = content + swap_endian(sc->stroff, need_swap);
	symbol->name = stringtable + swap_endian(array[i].n_un.n_strx, need_swap);
}

void						get_symbol_value_64(void *content, uint32_t i, struct symtab_command *sc, t_symbol *symbol, int need_swap)
{
	struct nlist_64			*array;
	uint8_t					n_type_value;

	array = (void*)content + swap_endian(sc->symoff, need_swap);
	if ((n_type_value = (swap_endian(array[i].n_type, need_swap) & N_TYPE)))
		symbol->value = swap_endian(array[i].n_value, need_swap);
}

void						parse_symtable_64(t_symbol **sym_head, void *content, struct symtab_command *sc, int need_swap)
{
	uint32_t				i;
	t_symbol				*symbol;

	i = -1;
	while (++i < sc->nsyms)
	{
		if (check_stab_64(content, i, sc, need_swap))
			continue;
		symbol = new_symbol();	
		get_symbol_name_64(content, i, sc, symbol, need_swap);
		get_symbol_value_64(content, i, sc, symbol, need_swap);
		get_symbol_type_char_64(content, i, sc, symbol, need_swap);
		add_symbol_to_list(sym_head, symbol);
	}
}
