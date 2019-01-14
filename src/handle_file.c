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

t_file					check_file(char *command, char *filename)
{
    t_file				file;
    int					fd;
	struct stat			stat_ret;

	ft_bzero(&file, sizeof(file));
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		perror_nosuchfile(command, filename);
		return (file);
	}
	if (fstat(fd, &stat_ret) < 0 || !(stat_ret.st_mode & S_IFREG))
	{
		//perror_fileerror(command, filename);
		return (file);
	}
	file.content = mmap(0, stat_ret.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);
	if (!file.content)
	{
		perror_maperror(command, filename);
		return (file);
	}
	file.name = filename;
	file.len = stat_ret.st_size;
	return (file);
}
