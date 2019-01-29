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

uint64_t		swap_endian(uint64_t x, int need_swap)
{
	if (need_swap)
		return (((((x) & 0xff000000) >> 24) | (((x) & 0xff0000) >> 8)\
		| (((x) & 0xff00) << 8) | (((x) & 0xff) << 24)));
	else
		return (x);
}

struct section				*handle_fat_header(t_symbol **sym_head, void *content, int need_swap)
{
	struct fat_header		*header;
	struct fat_arch			*arch;
	uint32_t				i;
	uint32_t				narch;

	i = -1;
	header = (struct fat_header*)content;
	narch = swap_endian(header->nfat_arch, need_swap);
	arch = (void*)content + sizeof(struct fat_header);
	while (++i < narch)
	{
		if ((cpu_type_t)swap_endian(arch[i].cputype, need_swap) == CPU_TYPE_X86_64)
			dispatch_by_magic((void*)(content + swap_endian(arch[i].offset, need_swap)), sym_head);
	}
	return (NULL);
}

struct section				*handle_32_header(t_symbol **sym_head, void *content, uint32_t nsect, int need_swap)
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct section			*sect;
	uint32_t				ncmds;
	uint32_t				i;

	i = -1;
	header = (struct mach_header*)content;
	ncmds = swap_endian(header->ncmds, need_swap);
	lc = (void*)content + sizeof(struct mach_header);
	sect = NULL;
	while (++i < ncmds)
	{
		if (nsect && swap_endian(lc->cmd, need_swap) == LC_SEGMENT)
			sect = parse_32_segments((struct segment_command*)lc, nsect, need_swap);
		else if (!nsect && swap_endian(lc->cmd, need_swap) == LC_SYMTAB)
			parse_symtable_32(sym_head, content, (struct symtab_command*)lc, need_swap);
		if (sect != NULL)
			return (sect);
		lc = (void*)lc + swap_endian(lc->cmdsize, need_swap);
	}
	return (NULL);
}

struct section_64			*handle_64_header(t_symbol **sym_head, void *content, uint32_t nsect, int need_swap)
{
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct section_64		*sect;
	uint32_t				ncmds;
	uint32_t				i;

	i = -1;
	header = (struct mach_header_64*)content;
	ncmds = swap_endian(header->ncmds, need_swap);
	lc = (void*)content + sizeof(struct mach_header_64);
	sect = NULL;
	while (++i < ncmds)
	{
		if (nsect && swap_endian(lc->cmd, need_swap) == LC_SEGMENT_64)
			sect = parse_64_segments((struct segment_command_64*)lc, nsect, need_swap);
		else if (!nsect && swap_endian(lc->cmd, need_swap) == LC_SYMTAB)
			parse_symtable_64(sym_head, content, (struct symtab_command*)lc, need_swap);
		if (sect != NULL)
			return (sect);
		lc = (void*)lc + swap_endian(lc->cmdsize, need_swap);
	}
	return (NULL);
}
