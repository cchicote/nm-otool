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

void					ft_nm(char *filename)
{
	t_file				file;
	uint32_t			magic;

	file = check_file("ft_nm", filename);
	if (!file.content)
		return ;
	magic = *(uint32_t*)file.content;
	//ft_putendl(file.name);
	if (magic == MH_MAGIC_64)
	{
		handle_64_header(file.content);
	}
}

int						main(int argc, char **argv)
{
	int					i;

	i = 0;
	if (argc < 2)
		ft_nm("a.out");
	else
	{
		while (++i < argc)
		{
			ft_nm(argv[i]);
		}
	}
	return (EXIT_SUCCESS);
}