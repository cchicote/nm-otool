/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 17:29:42 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/21 17:29:56 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							ft_otool(char *filename)
{
	t_file					file;

	file = check_file("ft_otool", filename);
	if (!file.content)
		return (EXIT_FAILURE);
	if (ft_strncmp(file.content, ARMAG, SARMAG) == 0)
		return (handle_archive(&file));
	else if (dispatch_by_magic(&file) == EXIT_FAILURE)
		return (unmap_file_failure(&file, EXIT_FAILURE));
	print_t_sect(&file, NULL);
	unmap_file(&file);
	return (EXIT_SUCCESS);
}

int						main(int argc, char **argv)
{
	int					i;

	i = 0;

	if (argc < 2)
		perror_missing_file("ft_otool");
	else
	{
		while (++i < argc)
		{
			if (ft_otool(argv[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	while (1)
	;
	return (EXIT_SUCCESS);
}