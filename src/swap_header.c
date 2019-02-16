/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:08:45 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/16 18:08:51 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						swap_32_header(t_file *file, uint32_t offset)
{
	struct mach_header		*mach_header;

	mach_header = file->content + offset;
	SWAP(mach_header->cputype);
	SWAP(mach_header->cpusubtype);
	SWAP(mach_header->filetype);
	SWAP(mach_header->ncmds);
	SWAP(mach_header->sizeofcmds);
	SWAP(mach_header->flags);
}

void						swap_64_header(t_file *file, uint32_t offset)
{
	struct mach_header_64	*mach_header_64;
	
	mach_header_64 = file->content + offset;
	SWAP(mach_header_64->cputype);
	SWAP(mach_header_64->cpusubtype);
	SWAP(mach_header_64->filetype);
	SWAP(mach_header_64->ncmds);
	SWAP(mach_header_64->sizeofcmds);
	SWAP(mach_header_64->flags);
	SWAP(mach_header_64->reserved);
}

void						swap_fat_header(t_file *file, uint32_t offset)
{
	struct fat_header		*fat_header;

	fat_header = file->content + offset;
    SWAP(fat_header->nfat_arch);
}

void						swap_fat_arch(t_file *file, uint32_t offset, uint32_t i)
{
	struct fat_arch			*fat_arch;

	fat_arch = file->content + offset;
	SWAP(fat_arch[i].cputype);
	SWAP(fat_arch[i].cpusubtype);
	SWAP(fat_arch[i].offset);
	SWAP(fat_arch[i].size);
	SWAP(fat_arch[i].align);
}
