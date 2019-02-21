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

t_file						generate_file_from_archive_nm(char *command, char *ar_name, void *hdr_ptr)
{
	t_file					file;
	uint32_t				size;
	char					*filename;

	size = get_file_size_from_ar_hdr(hdr_ptr);
	filename = hdr_ptr + sizeof(struct ar_hdr);
	ft_bzero(&file, sizeof(t_file));
	file.content = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
	if (!file.content)
	{
		perror_maperror(command, filename);
		return (file);
	}
	file.content = hdr_ptr+ sizeof(struct ar_hdr)
		+ get_name_size_from_ar_hdr(hdr_ptr);
	file.name = filename;
	file.len = size;
	file.command = ft_strdup(command);
	if (dispatch_by_magic(&file) == EXIT_FAILURE)
		return (file);
	sort_arch_symbols(&file);
	print_arch_sym(&file, TRUE, ar_name);
	return (file);
}

t_file						generate_file_from_archive_otool(char *command, char *ar_name, void *hdr_ptr)
{
	t_file					file;
	uint32_t				size;
	char					*filename;

	size = get_file_size_from_ar_hdr(hdr_ptr);
	filename = hdr_ptr + sizeof(struct ar_hdr);
	ft_bzero(&file, sizeof(t_file));
	file.content = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, -1, 0);
	if (!file.content)
	{
		perror_maperror(command, filename);
		return (file);
	}
	file.content = hdr_ptr+ sizeof(struct ar_hdr)
		+ get_name_size_from_ar_hdr(hdr_ptr);
	file.name = filename;
	file.len = size;
	file.command = ft_strdup(command);
	if (dispatch_by_magic(&file) == EXIT_FAILURE)
		return (file);
	print_t_sect(&file, ar_name);
	return (file);
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
				file->content + curr_offset);
		else if (ft_strcmp(file->command, "ft_otool") == 0)
			generate_file_from_archive_otool(file->command, file->name,
			file->content + curr_offset);
		curr_offset += get_file_size_from_ar_hdr(file->content + curr_offset)
			+ sizeof(struct ar_hdr);
	}
	return (EXIT_SUCCESS);
}
