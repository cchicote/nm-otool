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

int							lc_is_32_segment(t_file *file, t_arch *arch, struct load_command *lc, uint32_t i)
{
	if (arch->is_little_endian)
		swap_32_segment_command((struct segment_command*)lc);
	if (!ft_strcmp(file->command, "ft_nm")
		&& (check_segment_32(file, lc->cmdsize, (struct segment_command*)lc,
		i) == EXIT_FAILURE || parse_32_segments(file,
		(struct segment_command*)lc, arch, i) == EXIT_FAILURE))
		return (EXIT_FAILURE);
	else if (!ft_strcmp(file->command, "ft_otool")
		&& (check_segment_32(file, lc->cmdsize, (struct segment_command*)lc,
		i) == EXIT_FAILURE || get_32_text_sect_addr(file,
		(struct segment_command*)lc, arch, i) == EXIT_FAILURE))
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
	arch->addr = (void*)header;
	file->curr_arch = (void*)header;
	file->curr_header_end = (void*)header + sizeof(struct mach_header)
		+ header->sizeofcmds;
}

int							handle_otool_32_header(t_file *file, t_arch *arch)
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
		lc = (void*)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

int							handle_nm_32_header(t_file *file, t_arch *arch)
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
