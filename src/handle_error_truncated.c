/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_truncated.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 19:11:16 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/15 19:11:23 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						perror_truncated_malformed_file(char *command,
								char *filename, uint32_t failing_lc)
{
	perror_command(command);
	perror_filename(filename);
	ft_putstr("truncated or malformed object (load command ");
	ft_putnbr(failing_lc);
	ft_putendl(" extends past the end of file)");
}

void						perror_truncated_malformed_multiple(char *command,
								char *filename, uint32_t failing_lc)
{
	perror_command(command);
	perror_filename(filename);
	ft_putstr("truncated or malformed object (load command ");
	ft_putnbr(failing_lc);
	ft_putendl(" cmdsize not a multiple of 4)");
}

void						perror_truncated_malformed_lc(char *command,
								char *filename, uint32_t failing_lc)
{
	perror_command(command);
	perror_filename(filename);
	ft_putstr("truncated or malformed object (load command ");
	ft_putnbr(failing_lc);
	ft_putendl(" extends past the end all load commands in the file)");
}

void						perror_truncated_malformed_seg_eof(char *command,
								char *filename, char *segname,
								uint32_t failing_seg)
{
	perror_command(command);
	perror_filename(filename);
	ft_putstr("truncated or malformed object (load command ");
	ft_putnbr(failing_seg);
	ft_putstr(" fileoff field plus filesize field in ");
	ft_putstr(segname);
	ft_putendl(" extends past the end of the file)");
}

void						perror_truncated_malformed_seg_nsect(char *command,
								char *filename, char *segname,
								uint32_t failing_seg)
{
	perror_command(command);
	perror_filename(filename);
	ft_putstr("truncated or malformed object (load command ");
	ft_putnbr(failing_seg);
	ft_putstr(" inconsistent cmdsize in ");
	ft_putstr(segname);
	ft_putendl(" for the number of sections)");
}
