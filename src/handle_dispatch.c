/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:57:21 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/18 17:57:26 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							dispatch_by_magic(t_file *file)
{
	static uint32_t			magic = 0;

	magic = *(uint32_t*)file->content;
	file->is_little_endian = (magic == MH_CIGAM || magic == MH_CIGAM_64
		|| magic == FAT_CIGAM);
	file->is_fat = (magic == FAT_MAGIC || magic == FAT_CIGAM);
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		return (handle_fat_header(file));
	else if (magic == MH_MAGIC || magic == MH_CIGAM || magic == MH_MAGIC_64
		|| magic == MH_CIGAM_64)
		return (handle_new_arch(file, 0));
	else
	{
		perror_fileerror(file->command, file->name);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
