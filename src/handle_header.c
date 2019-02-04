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

void						handle_fat_header(t_file *file)
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
		{
			file->display_multiple_cpu = FALSE;
			handle_new_arch(file, fat_arch[i].offset);
			return ;
		}
	}
	file->display_multiple_cpu = TRUE;
	i = -1;
	while (++i < narch)
	{
		if ((cpu_type_t)fat_arch[i].cputype == CPU_TYPE_I386)
			handle_new_arch(file, fat_arch[i].offset);
		else if ((cpu_type_t)fat_arch[i].cputype == CPU_TYPE_POWERPC)
			handle_new_arch(file, fat_arch[i].offset);
	}
}

void						handle_new_arch(t_file *file, uint32_t offset)
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
		if (magic == MH_CIGAM)
			swap_32_header(file, offset);
		new_arch->name_int = ARCH_32;
		handle_32_header(file, new_arch);
	}
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	{
		if (magic == MH_CIGAM_64)
			swap_64_header(file, offset);
		new_arch->name_int = ARCH_64;
		handle_64_header(file, new_arch);
	}
	add_arch_to_list(file, new_arch);
}

void						handle_32_header(t_file *file, t_arch *arch)
{
	struct load_command		*lc;
	struct mach_header		*header;
	uint32_t				ncmds;
	uint32_t				i;

	i = -1;
	header = file->content + arch->offset;
	arch->cputype = header->cputype;
	ncmds = header->ncmds;
	lc = file->content + arch->offset + sizeof(struct mach_header);
	while (++i < ncmds)
	{
		if (arch->is_little_endian)
			swap_load_command(lc);
		if (lc->cmd == LC_SEGMENT)
		{
			if (arch->is_little_endian)
				swap_32_segment_command((struct segment_command*)lc);
			parse_32_segments(file, (struct segment_command*)lc, arch);
		}
		else if (lc->cmd == LC_SYMTAB)
		{
			if (arch->is_little_endian)
				swap_symtab_command((struct symtab_command*)lc);
			parse_symtable_32(file, (struct symtab_command*)lc, arch);
		}
		lc = (void*)lc + lc->cmdsize;
	}
}

void						handle_64_header(t_file *file, t_arch *arch)
{
	struct load_command		*lc;
	struct mach_header_64	*header;
	uint32_t				ncmds;
	uint32_t				i;

	i = -1;
	header = file->content + arch->offset;
	arch->cputype = header->cputype;
	ncmds = header->ncmds;
	lc = file->content + arch->offset + sizeof(struct mach_header_64);
	while (++i < ncmds)
	{
		if (arch->is_little_endian)
			swap_load_command(lc);
		if (lc->cmd == LC_SEGMENT_64)
		{
			if (arch->is_little_endian)
				swap_64_segment_command((struct segment_command_64*)lc);
			parse_64_segments(file, (struct segment_command_64*)lc, arch);
		}
		else if (lc->cmd == LC_SYMTAB)
		{
			if (arch->is_little_endian)
				swap_symtab_command((struct symtab_command*)lc);
			parse_symtable_64(file, (struct symtab_command*)lc, arch);
		}
		lc = (void*)lc + lc->cmdsize;
	}
}

