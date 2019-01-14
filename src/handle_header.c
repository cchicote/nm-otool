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

void						print_symtable(uint32_t nsyms, uint32_t symoff, uint32_t stroff, char *content)
{
	uint32_t				i;
	struct nlist_64			*array;
	char					*stringtable;

	i = 0;
	array = (void*)content + symoff;
	stringtable = (void*)content + stroff;
	while (i < nsyms)
	{
		ft_putendl(stringtable + array[i].n_un.n_strx);
		ft_putendl(stringtable + array[i].n_type);
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
			print_symtable(sym->nsyms, sym->symoff, sym->stroff, content);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
	}
}