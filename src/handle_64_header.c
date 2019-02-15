/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:02:36 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/15 19:02:44 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							handle_64_arch(t_file *file, t_arch *arch, uint32_t magic, uint32_t offset)
{
	file->display_multiple_cpu++;
	if (magic == MH_CIGAM_64)
		swap_64_header(file, offset);
	arch->name_int = ARCH_64;
	if (handle_64_header(file, arch) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	add_arch_to_list(file, arch);
	return (EXIT_SUCCESS);
}

int							lc_is_64_segment(t_file *file, t_arch *arch, struct load_command *lc, uint32_t i)
{
	if (arch->is_little_endian)
		swap_64_segment_command((struct segment_command_64*)lc);
	if (check_segment_64(file, lc->cmdsize, (struct segment_command_64*)lc, i)
		== EXIT_FAILURE || parse_64_segments(file,
		(struct segment_command_64*)lc, arch, i) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void						lc_is_64_symtab(t_file *file, t_arch *arch, struct load_command *lc)
{
	if (arch->is_little_endian)
		swap_symtab_command((struct symtab_command*)lc);
	parse_symtable_64(file, (struct symtab_command*)lc, arch);
}

void						update_64_header_values(t_file *file, t_arch *arch, struct mach_header_64 *header)
{
	arch->cputype = header->cputype;
	file->curr_arch = (void*)header;
	file->curr_header_end = (void*)header + sizeof(struct mach_header_64)
		+ header->sizeofcmds;
}

int							handle_64_header(t_file *file, t_arch *arch)
{
	struct load_command		*lc;
	struct mach_header_64	*header;
	uint32_t				ncmds;
	uint32_t				i;

	i = -1;
	header = file->content + arch->offset;
	update_64_header_values(file, arch, header);
	ncmds = header->ncmds;
	lc = file->content + arch->offset + sizeof(struct mach_header_64);
	while (++i < ncmds)
	{
		if (arch->is_little_endian)
			swap_load_command(lc);
		if (check_lc(file, (void*)lc, (void*)header + header->sizeofcmds
			+ sizeof(struct mach_header_64), i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SEGMENT_64
			&& lc_is_64_segment(file, arch, lc, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if (lc->cmd == LC_SYMTAB)
			lc_is_64_symtab(file, arch, lc);
		lc = (void*)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
