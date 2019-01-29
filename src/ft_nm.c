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

void					print_symbols(t_symbol **sym_head, int IS_64)
{
	t_symbol 			*tmp;

	tmp = *sym_head;
	//printf("SYMBOLS: \n");
	while (tmp)
	{
		if (tmp->value && IS_64)
			printf("%016llx %c %s\n", tmp->value, tmp->type_char, tmp->name);
		else if (tmp->value && !IS_64)
			printf("%08llx %c %s\n", tmp->value, tmp->type_char, tmp->name);
		else if (IS_64)
			printf("%16s %c %s\n", " ", tmp->type_char, tmp->name);
		else
			printf("%8s %c %s\n", " ", tmp->type_char, tmp->name);
		tmp = tmp->next;
	}
	//printf("\n");
}

uint32_t				dispatch_by_magic(void *content, t_symbol **sym_head)
{
	static uint32_t		magic = 0;

	magic = *(uint32_t*)content;
	if (magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_64_header(sym_head, content, 0, magic == MH_CIGAM_64);
	else if (magic == MH_MAGIC || magic == MH_CIGAM)
		handle_32_header(sym_head, content, 0, magic == MH_CIGAM);
	else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
		handle_fat_header(sym_head, content, magic == FAT_CIGAM);
	return (magic);
}

void					ft_nm(char *filename, int multiple_files)
{
	t_symbol			*sym_head;
	t_file				file;
	uint32_t			magic;

	sym_head = NULL;
	file = check_file("ft_nm", filename);
	if (!file.content)
		return ;
	if (multiple_files)
		printf("\n%s:\n", file.name);
	magic = dispatch_by_magic(file.content, &sym_head);
	sort_symbols_by_name(&sym_head);
	print_symbols(&sym_head, magic == MH_MAGIC_64);
	//munmap(file.content, file.len);
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