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
** characters,  representing the symbol type: U (undefined), A (absolute),
** T (text section symbol), D (data section symbol), B (bss section symbol),
** C (common symbol), (for debugger symbol table entries; see -a below),
** S (symbol in a section other than those above), or I (indirect symbol).
** If the  symbol  is  local  (non-external),  the  symbol's type is instead
** represented by the corresponding lowercase letter.  A lower case u in a
** dynamic shared library indicates a undefined reference to a private external
** in another module in the same library.
*/

void						print_symtable_64(uint32_t nsyms, uint32_t symoff, uint32_t stroff, char *content)
{
	uint32_t				i;
	struct nlist_64			*array;
	char					*stringtable;

	i = 0;
	array = (void*)content + symoff;
	stringtable = (void*)content + stroff;
	while (i < nsyms)
	{
		if (array[i].n_type & N_STAB)
			ft_putstr("N_STAB\t");
		else if (array[i].n_type & N_PEXT)
			ft_putstr("N_PEXT\t");
		else if (array[i].n_type & N_TYPE)
		{
			if ((array[i].n_type & N_TYPE) == N_UNDF)
				ft_putstr("U\t");
			else if ((array[i].n_type & N_TYPE) == N_ABS)
				ft_putstr("A\t");
			else if ((array[i].n_type & N_TYPE) == N_SECT)
			{
				ft_putstr("S\t");
				ft_putnbr(array[i].n_sect);
			}
			else if ((array[i].n_type & N_TYPE) == N_PBUD)
				ft_putstr("P\t");
			else if ((array[i].n_type & N_TYPE) == N_INDR)
				ft_putstr("I\t");
			else 
				ft_putstr("N_TYPE\t");
		}
		else if (array[i].n_type & N_EXT)
		{
			ft_putstr("N_EXT\t");
			ft_putnbr(array[i].n_type);
		}
		else
			ft_putstr("ERR\t");
		ft_putendl(stringtable + array[i].n_un.n_strx);
		i++;
	}
}

void						handle_64_header(char *content)
{
	struct mach_header_64	*header;
	uint32_t				ncmds;
	struct load_command		*lc;
	uint32_t				i;
	struct symtab_command	*sym;

	i = -1;
	header = (struct mach_header_64*)content;
	ncmds = header->ncmds;
	lc = (void*)content + sizeof(struct mach_header_64);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			print_symtable_64(sym->nsyms, sym->symoff, sym->stroff, content);
			break ;
		}
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

void						handle_32_header(char *content)
{
	struct mach_header		*header;
	uint32_t				ncmds;
	struct load_command		*lc;
	uint32_t				i;
	struct symtab_command	*sym;

	i = -1;
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
