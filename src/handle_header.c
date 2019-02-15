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
	file->is_little_endian ? swap_fat_header(file, 0) : 0;
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
		if (((cpu_type_t)fat_arch[i].cputype == CPU_TYPE_I386
			&& handle_new_arch(file, fat_arch[i].offset) == EXIT_FAILURE)
			|| ((cpu_type_t)fat_arch[i].cputype == CPU_TYPE_POWERPC
			&& handle_new_arch(file, fat_arch[i].offset) == EXIT_FAILURE))
			return (EXIT_FAILURE);
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
		if (handle_32_arch(file, new_arch, magic, offset) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
	{
		if (handle_64_arch(file, new_arch, magic, offset) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
