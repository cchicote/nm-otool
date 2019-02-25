/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:14:47 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/06 19:14:52 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm_otool.h>

uint32_t					get_name_size_from_ar_hdr(void *hdr_ptr)
{
	uint32_t				name_size;

	name_size = (uint32_t)ft_atoi(hdr_ptr + 3);
	return (name_size);
}

uint32_t					get_file_size_from_ar_hdr(void *hdr_ptr)
{
	uint32_t				size;

	size = (uint32_t)ft_atoi(hdr_ptr + 48);
	return (size);
}

uint32_t					parse_ar_symtab_max_offset(void *content)
{
	uint32_t				offset;
	uint32_t				size;
	uint32_t				symtab_size;
	uint32_t				offset_max;

	offset = SARMAG + sizeof(struct ar_hdr) + 20 + sizeof(uint32_t) * 2;
	size = 0;
	offset_max = 0;
	symtab_size = *(uint32_t*)(content + offset - 2 * sizeof(uint32_t));
	while (size < symtab_size)
	{
		offset_max = *(uint32_t*)(content + offset)
			> offset_max ? *(uint32_t*)(content + offset) : offset_max;
		offset += sizeof(uint32_t) * 2;
		size = size + sizeof(uint32_t) + sizeof(uint32_t);
	}
	return (offset_max);
}

int							handle_archive(t_file *file)
{
	uint32_t				offset_max;
	uint32_t				curr_offset;

	curr_offset = get_file_size_from_ar_hdr(file->content + SARMAG)
		+ sizeof(struct ar_hdr) + SARMAG;
	offset_max = parse_ar_symtab_max_offset(file->content);
	if (ft_strcmp(file->command, "ft_otool") == 0)
	{
		ft_putstr("Archive : ");
		ft_putendl(file->name);
	}
	while (curr_offset <= offset_max)
	{
		if (ft_strcmp(file->command, "ft_nm") == 0)
			generate_file_from_archive_nm(file->command, file->name,
				file->content + curr_offset, file->options);
		else if (ft_strcmp(file->command, "ft_otool") == 0)
			generate_file_from_archive_otool(file->command, file->name,
			file->content + curr_offset, init_options());
		curr_offset += get_file_size_from_ar_hdr(file->content + curr_offset)
			+ sizeof(struct ar_hdr);
	}
	unmap_file(file);
	return (EXIT_SUCCESS);
}
