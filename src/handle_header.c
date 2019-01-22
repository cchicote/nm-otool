/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:01:49 by cchicote          #+#    #+#             */
/*   Updated: 2019/01/11 17:02:01 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

/*
** Each symbol name is preceded by its value (blanks if undefined).  Unless the
** -m option is specified, this value is followed by one of  the  following
** characters,  representing the symbol type: 
** A (absolute),
** B (bss section symbol),
** C (common symbol) (for debugger symbol table entries; see -a below),
** D (data section symbol), 
** I (indirect symbol).
** S (symbol in a section other than those above), 
** T (text section symbol), 
** U (undefined), 
** If the  symbol  is  local  (non-external),  the  symbol's type is instead
** represented by the corresponding lowercase letter.  A lower case u in a
** dynamic shared library indicates a undefined reference to a private external
** in another module in the same library.
*/

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

	new = (t_symbol*)malloc(sizeof(t_symbol));
	ft_bzero(new, sizeof(t_symbol));
	return (new);
}

void						print_sym_value(t_symbol *symbol, struct nlist_64 sym)
{
	uint8_t					n_type_value;

	if ((n_type_value = (sym.n_type & N_TYPE)))
		symbol->value = sym.n_value;
	/*if ((n_type_value = (sym.n_type & N_TYPE)))
		printf("%016llx ", sym.n_value);
	else
		printf("%16s ", " ");*/
}

void						print_sym_name(t_symbol *symbol, char *stringtable, struct nlist_64 sym)
{
	symbol->name = ft_strdup(stringtable + sym.n_un.n_strx);
	//printf("%s\n", stringtable + sym.n_un.n_strx);
}

void						print_sym_type(t_symbol *symbol, struct nlist_64 sym)
{
	uint8_t					n_type_value;
	
	symbol->section_index = NO_SECT;
	if (sym.n_type & N_STAB)
		symbol->type_char = 'B';
	else if (sym.n_type & N_PEXT)
		symbol->type_char = 'X';
	else if ((n_type_value = (sym.n_type & N_TYPE)))
	{
		if (n_type_value == N_UNDF)
			symbol->type_char = 'U';
		else if (n_type_value == N_ABS)
			symbol->type_char = 'A';
		else if (n_type_value == N_SECT)
		{
			symbol->section_index = sym.n_sect;
			symbol->type_char = 'S';
		}
		else if (n_type_value == N_PBUD)
			symbol->type_char = 'P';
		else if (n_type_value == N_INDR)
			symbol->type_char = 'I';
		else 
			symbol->type_char = 'N';
	}
	else if (sym.n_type & N_EXT)
		symbol->type_char = 'E';
	else /*error*/
		symbol->type_char = 'R';
}

void						print_symtable_64(t_symbol **sym_head, uint32_t nsyms, uint32_t symoff, uint32_t stroff, char *content)
{
	uint32_t				i;
	struct nlist_64			*array;
	char					*stringtable;
	t_symbol				*symbol;

	i = 0;
	array = (void*)content + symoff;
	stringtable = (void*)content + stroff;
	while (i < nsyms)
	{
		symbol = new_symbol();
		print_sym_value(symbol, array[i]);
		print_sym_type(symbol, array[i]);
		print_sym_name(symbol, stringtable, array[i]);
		add_symbol_to_list(sym_head, symbol);
		i++;
	}
}

void						read_load_command(t_symbol **sym_head, struct load_command *lc, char *content)
{
	struct symtab_command	*sym;

	if (lc->cmd == LC_SYMTAB)
	{
		sym = (struct symtab_command*)lc;
		print_symtable_64(sym_head, sym->nsyms, sym->symoff, sym->stroff, content);
	}
}

void						read_seg_data(struct segment_command_64 *seg)
{
	if (!ft_strcmp(seg->segname, SEG_TEXT))
		ft_putendl(seg->segname);
	else if (!ft_strcmp(seg->segname, SEG_DATA))
		ft_putendl(seg->segname);
	else if (!ft_strcmp(seg->segname, SEG_PAGEZERO))
		ft_putendl(seg->segname);
}

void						handle_64_header(t_symbol **sym_head, char *content)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	uint32_t				ncmds;
	uint32_t				i;

	i = -1;
	header = (struct mach_header_64*)content;
	ncmds = header->ncmds;
	lc = (void*)content + sizeof(struct mach_header_64);
	while (++i < ncmds)
	{
		read_load_command(sym_head, lc, content);
		lc = (void*)lc + lc->cmdsize;
	}
}

void						print_symtable_32(uint32_t nsyms, uint32_t symoff, uint32_t stroff, char *content)
{
	uint32_t				i;
	struct nlist			*array;
	char					*stringtable;

	i = 0;
	array = (void*)content + symoff;
	stringtable = (void*)content + stroff;
	while (i < nsyms)
	{
		if (array[i].n_type == N_UNDF)
			ft_putstr("U\t");
		else if (array[i].n_type == N_ABS)
			ft_putstr("A\t");
		else if (array[i].n_type == N_SECT)
			ft_putstr("S\t");
		else if (array[i].n_type == N_PBUD)
			ft_putstr("P\t");
		else if (array[i].n_type == N_INDR)
			ft_putstr("I\t");
		else
			ft_putstr("NO TYPE\t");
		ft_putendl(stringtable + array[i].n_un.n_strx);
		i++;
	}
}

void						handle_32_header(t_symbol **sym_head, char *content)
{
	struct mach_header		*header;
	uint32_t				ncmds;
	struct load_command		*lc;
	uint32_t				i;
	struct symtab_command	*sym;

	i = -1;
	sym_head++;
	header = (struct mach_header*)content;
	ncmds = header->ncmds;
	lc = (void*)content + sizeof(struct mach_header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			print_symtable_32(sym->nsyms, sym->symoff, sym->stroff, content);
			break; 
		}
		lc = (void*)lc + lc->cmdsize;
	}
}
