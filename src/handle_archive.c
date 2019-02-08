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

void					print_object_header(void *header)
{
	printf("HEADER of [%s]\n\tTime: [%u]\n\tUid: [%u]\n\tGid: [%u]\n\tMode: [%u]\n\tSize: [%u]\n\n", header + sizeof(struct ar_hdr), (uint32_t)(ft_atoi(header + 16)), (uint32_t)(ft_atoi(header + 28)), (uint32_t)(ft_atoi(header + 34)), (uint32_t)(ft_atoi(header + 40)), (uint32_t)(ft_atoi(header + 48)));
}

uint32_t				parse_ar_symtab_max_offset(void *content)
{
	uint32_t			offset;
	uint32_t			size;
	uint32_t			symtab_size;
	uint32_t			offset_max;

	offset = SARMAG + sizeof(struct ar_hdr) + 20 + sizeof(uint32_t) * 2;
	size = 0;
	offset_max = 0;
	symtab_size = *(uint32_t*)(content + offset - 2 * sizeof(uint32_t));
	while (size < symtab_size)
	{
		offset_max = *(uint32_t*)(content + offset) > offset_max ? *(uint32_t*)(content + offset) : offset_max;
		offset += sizeof(uint32_t) * 2;
		size = size + sizeof(uint32_t) + sizeof(uint32_t);
	}
	return (offset_max);
}

int							handle_archive(t_file *file)
{
	uint32_t				offset_max;
	uint32_t				curr_offset;

	curr_offset = get_file_size_from_ar_hdr(file->content + SARMAG) + sizeof(struct ar_hdr) + SARMAG;
	offset_max = parse_ar_symtab_max_offset(file->content);
	while (curr_offset <= offset_max)
	{
		generate_file_from_archive("ft_nm", file->name, file->content + curr_offset);
		curr_offset += get_file_size_from_ar_hdr(file->content + curr_offset) + sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}

/*int						handle_archive(t_file *file)
{
	t_ar_header			ar_hdr;
	uint32_t			offset;
	uint32_t			next_object;
	uint32_t			size;
	uint32_t			symtab_size;

	ar_hdr.ar_header = file->content + SARMAG;
 	ft_strncpy(ar_hdr.long_name, (char*)ar_hdr.ar_header + sizeof(struct ar_hdr), 20);
	if (ft_strncmp(ar_hdr.ar_header->ar_name, AR_EFMT1, 3))
	{
		printf("ERROR ARCHIVE [%s]\n", file->name);
		return (EXIT_FAILURE);
	}
	offset = SARMAG + sizeof(struct ar_hdr) + 20 + sizeof(uint32_t) * 2;
	size = 0;
	symtab_size = *(uint32_t*)(file->content + offset - 2 * sizeof(uint32_t));
	next_object = sizeof(struct ar_hdr) + SARMAG + (uint32_t)ft_atoi(file->content + SARMAG + 48);
	printf("MAX OFFSET: %p\n", get_ar_last_sym_offset(file->content));
	//printf("offset: [%p]\tsize: [%u]\tsymtab_size: [%u]\n", offset, size, symtab_size);
	while (size < symtab_size)
	{
		//printf("offset: [%p]\nNext: [%p]\n\n", offset, next_object);
		//next_object += get_file_size_from_ar_hdr(file->content + next_object) + sizeof(struct ar_hdr);
		//generate_file_from_archive("ft_nm", file->name, file->content + *(uint32_t*)(file->content + offset));
		offset += sizeof(uint32_t) * 2;
		size = size + sizeof(uint32_t) + sizeof(uint32_t);
	}
	return (EXIT_SUCCESS);
}*/