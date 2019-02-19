/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:27:50 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/21 17:27:59 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							ft_nm(char *filename, int multiple_files)
{
	t_file					file;

	file = check_file("ft_nm", filename);
	if (!file.content)
		return (EXIT_FAILURE);
	if (ft_strncmp(file.content, ARMAG, SARMAG) == 0)
		return (handle_archive(&file));
	else if (dispatch_by_magic(&file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	sort_arch_symbols(&file);
	print_arch_sym(&file, multiple_files, NULL);
	unmap_file(&file);
	return (EXIT_SUCCESS);
}

int						main(int argc, char **argv)
{
	int					i;

	i = 0;

	if (argc < 2)
		ft_nm("a.out", argc > 2);
	else
	{
		while (++i < argc)
		{
			ft_nm(argv[i], argc > 2);
		}
	}
	return (EXIT_SUCCESS);
}