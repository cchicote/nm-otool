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

void					print_filename_and_cpu(t_arch *arch, char *filename)
{
	printf("\n%s (for architecture ", filename);
	if (arch->cputype == CPU_TYPE_X86_64)
		printf("x86_64");
	else if (arch->cputype == CPU_TYPE_I386)
		printf("i386");
	else if (arch->cputype == CPU_TYPE_POWERPC)
		printf("ppc");
	else if (arch->cputype == CPU_TYPE_POWERPC64)
		printf("ppc64");
	else if (arch->cputype == CPU_TYPE_ARM)
		printf("arm");
	else if (arch->cputype == CPU_TYPE_ARM64)
		printf("arm64");
	else if (arch->cputype == CPU_TYPE_SPARC)
		printf("sparc");
	else if (arch->cputype == CPU_TYPE_I860)
		printf("i860");
	else if (arch->cputype == CPU_TYPE_HPPA)
		printf("hppa");
	else if (arch->cputype == CPU_TYPE_MC680x0)
		printf("mc680x0");
	else if (arch->cputype == CPU_TYPE_MC98000)
		printf("mc98000");
	else if (arch->cputype == CPU_TYPE_MC88000)
		printf("mc88000");
	else
		printf("unknown");
	printf("):\n");
}

void					print_symbols(t_arch *arch, int IS_64)
{
	t_symbol 			*tmp;

	tmp = arch->sym_head;
	while (tmp)
	{
		if (tmp->type_char == '?')
			tmp->type_char = arch->sect_char[tmp->section_index];
		if (tmp->is_external)
			tmp->type_char = ft_toupper(tmp->type_char);
		if (ft_toupper(tmp->type_char) != 'U' && IS_64)
			printf("%016llx %c %s\n", tmp->value, tmp->type_char, tmp->name);
		else if (ft_toupper(tmp->type_char) != 'U' && !IS_64)
			printf("%08llx %c %s\n", tmp->value, tmp->type_char, tmp->name);
		else if (IS_64)
			printf("%16s %c %s\n", " ", tmp->type_char, tmp->name);
		else
			printf("%8s %c %s\n", " ", tmp->type_char, tmp->name);
		tmp = tmp->next;
	}
}

void					print_arch_sym(t_file *file, int multiple_files, char *ar_name)
{
	t_arch				*tmp;

	tmp = file->arch;
	if (!file->is_fat)
	{
		if (ar_name)
			printf("\n%s(%s):\n", ar_name, file->name);
		else if (multiple_files)
			printf("\n%s:\n", file->name);
		print_symbols(tmp, tmp->name_int == ARCH_64);
		return ;
	}
	while (tmp)
	{
		if (file->display_multiple_cpu)
			print_filename_and_cpu(tmp, file->name);
		else if (ar_name)
			printf("\n%s(%s):\n", ar_name, file->name);
		else if (multiple_files)
			printf("\n%s:\n", file->name);
		print_symbols(tmp, tmp->name_int == ARCH_64);
		tmp = tmp->next;
	}
}

int						dispatch_by_magic(t_file *file)
{
	static uint32_t		magic = 0;

	magic = *(uint32_t*)file->content;
	file->is_little_endian = (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM);
	file->is_fat = (magic == FAT_MAGIC || magic == FAT_CIGAM);
	if (magic == FAT_MAGIC || magic == FAT_CIGAM)	
		handle_fat_header(file);
	else if (magic == MH_MAGIC || magic == MH_CIGAM || magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
		handle_new_arch(file, 0);
	else
	{
		perror_fileerror("ft_nm", file->name);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int						ft_nm(char *filename, int multiple_files)
{
	t_file				file;

	file = check_file("ft_nm", filename);
	if (!file.content)
		return (EXIT_FAILURE);
	if (ft_strncmp(file.content, ARMAG, SARMAG) == 0)
		return (handle_archive(&file));
	else if (dispatch_by_magic(&file) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	sort_arch_symbols(&file);
	print_arch_sym(&file, multiple_files, NULL);
	return (EXIT_SUCCESS);
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