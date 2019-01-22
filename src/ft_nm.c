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

void					print_symbols(t_symbol **sym_head)
{
	t_symbol 			*tmp;

	tmp = *sym_head;
	printf("SYMBOLS: \n");
	while (tmp)
	{
		if (tmp->value)
			printf("%016llx %c %s\n", tmp->value, tmp->type_char, tmp->name);
		else
			printf("%16s %c %s\n", " ", tmp->type_char, tmp->name);
		tmp = tmp->next;
	}
	printf("\n");
}

void					ft_nm(char *filename)
{
	t_file				file;
	uint32_t			magic;
	t_symbol			*sym_head;

	sym_head = NULL;
	file = check_file("ft_nm", filename);
	if (!file.content)
		return ;
	magic = *(uint32_t*)file.content;
	ft_putendl(file.name);
	if (magic == MH_MAGIC_64)
	{
		handle_64_header(&sym_head, file.content);
	}
	else if (magic == MH_MAGIC)
	{
		handle_32_header(&sym_head, file.content);
	}
	else
	{
		ft_putendl("Fichier non pris en compte");
	}
	print_symbols(&sym_head);
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