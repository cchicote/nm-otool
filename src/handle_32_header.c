/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:59:55 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/15 19:00:02 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							handle_32_arch(t_file *file, t_arch *arch, uint32_t magic, uint32_t offset)
{
	file->display_multiple_cpu++;
	if (magic == MH_CIGAM)
		swap_32_header(file, offset);
	arch->name_int = ARCH_32;
	if (handle_32_header(file, arch) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	add_arch_to_list(file, arch);
	return (EXIT_SUCCESS);
}

int							lc_is_32_segment(t_file *file, t_arch *arch, struct load_command *lc, uint32_t i)
{
	if (arch->is_little_endian)
		swap_32_segment_command((struct segment_command*)lc);
	if (check_segment_32(file, lc->cmdsize, (struct segment_command*)lc, i)
		== EXIT_FAILURE || parse_32_segments(file,
		(struct segment_command*)lc, arch, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void						lc_is_32_symtab(t_file *file, t_arch *arch, struct load_command *lc)
{
	if (arch->is_little_endian)
		swap_symtab_command((struct symtab_command*)lc);
	parse_symtable_32(file, (struct symtab_command*)lc, arch);
}

void						update_32_header_values(t_file *file, t_arch *arch, struct mach_header *header)
{
	arch->cputype = header->cputype;
	file->curr_arch = (void*)header;
	file->curr_header_end = (void*)header + sizeof(struct mach_header)
		+ header->sizeofcmds;
}

int							handle_32_header(t_file *file, t_arch *arch)
{
	struct load_command		*lc;
	struct mach_header		*header;
	uint32_t				ncmds;
	uint32_t				i;

	i = -1;
	header = file->content + arch->offset;
	update_32_header_values(file, arch, header);
	ncmds = header->ncmds;
	lc = file->content + arch->offset + sizeof(struct mach_header);
	while (++i < ncmds)
	{
		if (arch->is_little_endian)
			swap_load_command(lc);
		if (check_lc(file, (void*)lc, (void*)header + header->sizeofcmds
			+ sizeof(struct mach_header), i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SEGMENT
			&& lc_is_32_segment(file, arch, lc, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		else if (lc->cmd == LC_SYMTAB)
			lc_is_32_symtab(file, arch, lc);
		lc = (void*)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
