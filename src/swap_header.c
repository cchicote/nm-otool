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
	swap_endian((unsigned char*)&mach_header->cputype, sizeof(mach_header->cputype));
	swap_endian((unsigned char*)&mach_header->cpusubtype, sizeof(mach_header->cpusubtype));
	swap_endian((unsigned char*)&mach_header->filetype, sizeof(mach_header->filetype));
	swap_endian((unsigned char*)&mach_header->ncmds, sizeof(mach_header->ncmds));
	swap_endian((unsigned char*)&mach_header->sizeofcmds, sizeof(mach_header->sizeofcmds));
	swap_endian((unsigned char*)&mach_header->flags, sizeof(mach_header->flags));
}

void						swap_64_header(t_file *file, uint32_t offset)
{
	struct mach_header_64	*mach_header_64;
	
	mach_header_64 = file->content + offset;
	swap_endian((unsigned char*)&mach_header_64->cputype, sizeof(mach_header_64->cputype));
	swap_endian((unsigned char*)&mach_header_64->cpusubtype, sizeof(mach_header_64->cpusubtype));
	swap_endian((unsigned char*)&mach_header_64->filetype, sizeof(mach_header_64->filetype));
	swap_endian((unsigned char*)&mach_header_64->ncmds, sizeof(mach_header_64->ncmds));
	swap_endian((unsigned char*)&mach_header_64->sizeofcmds, sizeof(mach_header_64->sizeofcmds));
	swap_endian((unsigned char*)&mach_header_64->flags, sizeof(mach_header_64->flags));
	swap_endian((unsigned char*)&mach_header_64->reserved, sizeof(mach_header_64->reserved));
}

void						swap_fat_header(t_file *file, uint32_t offset)
{
	struct fat_header		*fat_header;

	fat_header = file->content + offset;
	swap_endian((unsigned char*)&fat_header->nfat_arch, sizeof(fat_header->nfat_arch));
}

void						swap_fat_arch(t_file *file, uint32_t offset, uint32_t i)
{
	struct fat_arch			*fat_arch;

	fat_arch = file->content + offset;
	swap_endian((unsigned char*)&fat_arch[i].cputype, sizeof(fat_arch[i].cputype));
	swap_endian((unsigned char*)&fat_arch[i].cpusubtype, sizeof(fat_arch[i].cpusubtype));
	swap_endian((unsigned char*)&fat_arch[i].offset, sizeof(fat_arch[i].offset));
	swap_endian((unsigned char*)&fat_arch[i].size, sizeof(fat_arch[i].size));
	swap_endian((unsigned char*)&fat_arch[i].align, sizeof(fat_arch[i].align));
}
