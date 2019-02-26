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

int							ft_nm(char *filename, char *options, int multiple_files)
{
	t_file					file;

	file = check_file("ft_nm", filename);
	if (!file.content)
		return (EXIT_FAILURE);
	file.options = options;
	if (ft_strncmp(file.content, ARMAG, SARMAG) == 0)
		return (handle_archive(&file));
	else if (dispatch_by_magic(&file) == EXIT_FAILURE)
		return (unmap_file_failure(&file, EXIT_FAILURE));
	sort_arch_symbols(&file);
	print_arch_sym(&file, multiple_files, NULL);
	unmap_file(&file);
	return (EXIT_SUCCESS);
}

int						main(int argc, char **argv)
{
	int					i;
	char				*options;

	i = 0;
	options = init_options();
	if (argc > 1 && argv[1][0] == '-')
	{
		if (parse_options(options, argv[1]) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (argc == 1 || (argc == 2 && argv[1][0] == '-'))
		ft_nm("a.out", options, FALSE);
	else if (argc > 1)
	{
		while (++i < argc)
		{
			ft_nm(argv[i], options, (argc > 2 && argv[1][0] != '-'));
		}
	}
	else
		perror_missing_file("ft_nm");
	return (EXIT_SUCCESS);
}