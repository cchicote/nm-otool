/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:01:49 by cchicote          #+#    #+#             */
/*   Updated: 2019/01/11 17:02:01 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

cpu_type_t					get_current_cpu_type(void)
{
	if (sizeof(void*) == 4)
		return (CPU_TYPE_I386);
	return (CPU_TYPE_X86_64);
}

int							check_valid_cpu_type(cpu_type_t cputype)
{
	if (cputype != get_current_cpu_type() && (cputype == CPU_TYPE_I386
		|| cputype == CPU_TYPE_X86_64 || cputype == CPU_TYPE_POWERPC))
		return (TRUE);
	return (FALSE);
}

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
		if ((cpu_type_t)fat_arch[i].cputype == get_current_cpu_type())
			return (handle_new_arch(file, fat_arch[i].offset));
	}
	i = -1;
	while (++i < narch)
		if (check_valid_cpu_type((cpu_type_t)fat_arch[i].cputype)
			&& handle_new_arch(file, fat_arch[i].offset) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
