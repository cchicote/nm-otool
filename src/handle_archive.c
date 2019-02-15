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
	while (curr_offset <= offset_max)
	{
		generate_file_from_archive("ft_nm", file->name, file->content
			+ curr_offset);
		curr_offset += get_file_size_from_ar_hdr(file->content + curr_offset)
			+ sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
