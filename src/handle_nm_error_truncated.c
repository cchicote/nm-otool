/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_nm_error_truncated.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 17:28:41 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/16 17:28:49 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						perror_nm_trunc_malf_sect_file(char *filename,
								uint32_t failing_sect, uint32_t failing_seg,
								char *segname)
{
	perror_command("ft_nm");
	perror_filename(filename);
	ft_putstr("truncated or malformed object (offset field of section ");
	ft_putnbr(failing_sect);
	ft_putstr(" in ");
	ft_putstr(segname);
	ft_putstr(" command ");
	ft_putnbr(failing_seg);
	ft_putendl(" extends past the end of the file)");
}

void						perror_nm_trunc_malf_sect_header(char *filename,
								uint32_t failing_sect, uint32_t failing_seg,
								char *segname)
{
	perror_command("ft_nm");
	perror_filename(filename);
	ft_putstr("truncated or malformed object (offset field of section ");
	ft_putnbr(failing_sect);
	ft_putstr(" in ");
	ft_putstr(segname);
	ft_putstr(" command ");
	ft_putnbr(failing_seg);
	ft_putendl(" not past the headers of the file)");
}
