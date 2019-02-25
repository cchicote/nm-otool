/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:24:23 by cchicote          #+#    #+#             */
/*   Updated: 2019/01/10 15:24:34 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						unmap_file(t_file *file)
{
	if (!ft_strcmp(file->command, "ft_nm"))
		free(file->options);
	free(file->command);
	munmap(file->content, file->len);
}

t_file						check_file(char *command, char *filename)
{
    t_file					file;
    int						fd;
	struct stat				stat_ret;

	ft_bzero(&file, sizeof(t_file));
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (perror_return(file, command, filename, &perror_nosuchfile));
	if (fstat(fd, &stat_ret) < 0 || !(stat_ret.st_mode & S_IFREG))
	{
		if (stat_ret.st_mode & S_IFDIR)
			perror_directory(command, filename);
		else
			perror_fileerror(command, filename);
		return (file);
	}
	file.content = mmap(0, stat_ret.st_size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	close(fd);
	if (!file.content)
		return (perror_return(file, command, filename, &perror_maperror));
	file.name = filename;
	file.len = stat_ret.st_size;
	file.command = ft_strdup(command);
	return (file);
}

int							generate_file_from_archive_nm(char *command, char *ar_name, void *hdr_ptr)
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
		return (EXIT_FAILURE);
	}
	file.content = hdr_ptr+ sizeof(struct ar_hdr)
		+ get_name_size_from_ar_hdr(hdr_ptr);
	file.name = filename;
	file.len = size;
	file.command = ft_strdup(command);
	if (dispatch_by_magic(&file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	sort_arch_symbols(&file);
	print_arch_sym(&file, TRUE, ar_name);
	unmap_file(&file);
	return (EXIT_SUCCESS);
}

int							generate_file_from_archive_otool(char *command, char *ar_name, void *hdr_ptr)
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
		return (EXIT_FAILURE);
	}
	file.content = hdr_ptr+ sizeof(struct ar_hdr)
		+ get_name_size_from_ar_hdr(hdr_ptr);
	file.name = filename;
	file.len = size;
	file.command = ft_strdup(command);
	if (dispatch_by_magic(&file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	print_t_sect(&file, ar_name);
	unmap_file(&file);
	return (EXIT_SUCCESS);
}
