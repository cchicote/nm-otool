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

int							handle_fat_header(t_file *file)
{
	struct fat_header		*fat_header;
	struct fat_arch			*fat_arch;
	uint32_t				i;
	uint32_t				narch;

	i = -1;
	if (file->is_little_endian)
		swap_fat_header(file, 0);
	fat_header = (struct fat_header*)file->content;
	fat_arch = file->content + sizeof(struct fat_header);
	narch = fat_header->nfat_arch;
	while (++i < narch)
	{
		if (file->is_little_endian)
			swap_fat_arch(file, sizeof(struct fat_header), i);
		if ((cpu_type_t)fat_arch[i].cputype == CPU_TYPE_X86_64)
			return (handle_new_arch(file, fat_arch[i].offset));
	}
	i = -1;
	while (++i < narch)
	{
		if ((cpu_type_t)fat_arch[i].cputype == CPU_TYPE_I386 && handle_new_arch(file, fat_arch[i].offset) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else if ((cpu_type_t)fat_arch[i].cputype == CPU_TYPE_POWERPC && handle_new_arch(file, fat_arch[i].offset) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int							handle_new_arch(t_file *file, uint32_t offset)
{
	uint32_t				magic;
	t_arch					*new_arch;

	magic = *(uint32_t*)(file->content + offset);
	new_arch = (t_arch*)ft_memalloc(sizeof(t_arch));
	ft_bzero(new_arch, sizeof(t_arch));
	new_arch->offset = offset;
	new_arch->is_little_endian = (magic == MH_CIGAM || magic == MH_CIGAM_64);
	if (magic == MH_MAGIC || magic == MH_CIGAM)
	{
		file->display_multiple_cpu++;
		if (magic == MH_CIGAM)
			swap_32_header(file, offset);
		new_arch->name_int = ARCH_32;
		if (handle_32_header(file, new_arch) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		add_arch_to_list(file, new_arch);
	}
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	{
		file->display_multiple_cpu++;
		if (magic == MH_CIGAM_64)
			swap_64_header(file, offset);
		new_arch->name_int = ARCH_64;
		if (handle_64_header(file, new_arch) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		add_arch_to_list(file, new_arch);
	}
	return (EXIT_SUCCESS);
}

int							handle_32_header(t_file *file, t_arch *arch)
{
	struct load_command		*lc;
	struct mach_header		*header;
	uint32_t				ncmds;
	uint32_t				i;

	i = -1;
	header = file->content + arch->offset;
	arch->cputype = header->cputype;
	file->curr_arch = (void*)header;
	file->curr_header_end = (void*)header + sizeof(struct mach_header) + header->sizeofcmds;
	ncmds = header->ncmds;
	lc = file->content + arch->offset + sizeof(struct mach_header);
	while (++i < ncmds)
	{
		if (arch->is_little_endian)
			swap_load_command(lc);
		if (check_lc(file, (void*)lc, (void*)header + header->sizeofcmds + sizeof(struct mach_header), i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SEGMENT)
		{
			if (arch->is_little_endian)
				swap_32_segment_command((struct segment_command*)lc);
			if (check_segment_32(file, lc->cmdsize, (struct segment_command*)lc, i) == EXIT_FAILURE || parse_32_segments(file, (struct segment_command*)lc, arch, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (lc->cmd == LC_SYMTAB)
		{
			if (arch->is_little_endian)
				swap_symtab_command((struct symtab_command*)lc);
			parse_symtable_32(file, (struct symtab_command*)lc, arch);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

int							handle_64_header(t_file *file, t_arch *arch)
{
	struct load_command		*lc;
	struct mach_header_64	*header;
	uint32_t				ncmds;
	uint32_t				i;

	i = -1;
	header = file->content + arch->offset;
	arch->cputype = header->cputype;
	file->curr_arch = (void*)header;
	file->curr_header_end = (void*)header + sizeof(struct mach_header_64) + header->sizeofcmds;
	ncmds = header->ncmds;
	lc = file->content + arch->offset + sizeof(struct mach_header_64);
	while (++i < ncmds)
	{
		if (arch->is_little_endian)
			swap_load_command(lc);
		if (check_lc(file, (void*)lc, (void*)header + header->sizeofcmds + sizeof(struct mach_header_64), i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (arch->is_little_endian)
				swap_64_segment_command((struct segment_command_64*)lc);
			if (check_segment_64(file, lc->cmdsize, (struct segment_command_64*)lc, i) == EXIT_FAILURE || parse_64_segments(file, (struct segment_command_64*)lc, arch, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (lc->cmd == LC_SYMTAB)
		{
			if (arch->is_little_endian)
				swap_symtab_command((struct symtab_command*)lc);
			parse_symtable_64(file, (struct symtab_command*)lc, arch);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}

