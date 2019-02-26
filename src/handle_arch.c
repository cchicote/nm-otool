/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:26:29 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/18 18:26:34 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							handle_new_arch(t_file *file, uint32_t offset)
{
	uint32_t				magic;
	t_arch					*new_arch;

	if (offset >= file->len)
	{
		perror_invalid_file(file->command, file->name);
		return (EXIT_FAILURE);
	}
	if (ft_strncmp(file->content + offset, ARMAG, SARMAG) == 0)
		return (handle_archive(file, offset));
	magic = *(uint32_t*)(file->content + offset);
	if ((new_arch = (t_arch*)ft_memalloc(sizeof(t_arch))) == NULL)
		return (EXIT_FAILURE);
	ft_bzero(new_arch, sizeof(t_arch));
	new_arch->offset = offset;
	new_arch->is_little_endian = (magic == MH_CIGAM || magic == MH_CIGAM_64);
	if (((magic == MH_MAGIC || magic == MH_CIGAM)
		&& handle_32_arch(file, new_arch, magic, offset) == EXIT_FAILURE)
		|| ((magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		&& handle_64_arch(file, new_arch, magic, offset) == EXIT_FAILURE))
	{
		free(new_arch);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int							handle_32_arch(t_file *file, t_arch *arch,
								uint32_t magic, uint32_t offset)
{
	file->display_multiple_cpu++;
	if (magic == MH_CIGAM)
		swap_32_header(file, offset);
	arch->name_int = ARCH_32;
	if (ft_strcmp(file->command, "ft_nm") == 0
		&& handle_nm_32_header(file, arch) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (ft_strcmp(file->command, "ft_otool") == 0
		&& handle_otool_32_header(file, arch) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	add_arch_to_list(file, arch);
	return (EXIT_SUCCESS);
}

int							handle_64_arch(t_file *file, t_arch *arch,
								uint32_t magic, uint32_t offset)
{
	file->display_multiple_cpu++;
	if (magic == MH_CIGAM_64)
		swap_64_header(file, offset);
	arch->name_int = ARCH_64;
	if (ft_strcmp(file->command, "ft_nm") == 0
		&& handle_nm_64_header(file, arch) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	else if (ft_strcmp(file->command, "ft_otool") == 0
		&& handle_otool_64_header(file, arch) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	add_arch_to_list(file, arch);
	return (EXIT_SUCCESS);
}
