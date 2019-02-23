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
