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

void					print_symbols(t_arch *arch, int IS_64)
{
	t_symbol 			*tmp;

	tmp = arch->sym_head;
	//printf("SYMBOLS: \n");
	while (tmp)
	{
		if (tmp->type_char == '?')
			tmp->type_char = arch->sect_char[tmp->section_index];
		if (tmp->is_external)
			tmp->type_char = ft_toupper(tmp->type_char);
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

void					print_arch_sym(t_file *file)
{
	t_arch				*tmp;

	tmp = file->arch;
	if (!file->is_fat)
	{
		print_symbols(tmp, tmp->name_int == ARCH_64);
		return ;
	}
	while (tmp)
	{
		print_symbols(tmp, tmp->name_int == ARCH_64);
		tmp = tmp->next;
	}
}

void					dispatch_by_magic(t_file *file)
{
	static uint32_t		magic = 0;

	magic = *(uint32_t*)file->content;
	file->is_little_endian = (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM);
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)
	{
		file->is_fat = TRUE;
		handle_fat_header(file);
	}
	else if (magic == MH_MAGIC || magic == MH_CIGAM || magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_new_arch(file, 0);
}

void					ft_nm(char *filename, int multiple_files)
{
	t_file				file;

	file = check_file("ft_nm", filename);
	if (!file.content)
		return ;
	if (multiple_files)
		printf("\n%s:\n", file.name);
	dispatch_by_magic(&file);
	sort_arch_symbols(&file);
	print_arch_sym(&file);
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