/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_symbols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 18:41:04 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/15 18:41:14 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						print_filename_and_cpu(t_arch *arch, char *filename)
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

void						print_symbols(t_arch *arch, int IS_64)
{
	t_symbol 				*tmp;
	t_symbol				*sym_to_free;
	char					*name;

	tmp = arch->sym_head;
	while (tmp)
	{
		if (!tmp->name)
			name = ft_strdup("bad string index");
		else
			name = ft_strdup(tmp->name);
		if (tmp->type_char == '?')
			tmp->type_char = arch->sect_char[tmp->section_index];
		if (tmp->is_external)
			tmp->type_char = ft_toupper(tmp->type_char);
		if (ft_toupper(tmp->type_char) != 'U' && IS_64)
			printf("%016llx %c %s\n", tmp->value, tmp->type_char, name);
		else if (ft_toupper(tmp->type_char) != 'U' && !IS_64)
			printf("%08llx %c %s\n", tmp->value, tmp->type_char, name);
		else if (IS_64)
			printf("%16s %c %s\n", " ", tmp->type_char, name);
		else
			printf("%8s %c %s\n", " ", tmp->type_char, name);
		sym_to_free = tmp;
		tmp = tmp->next;
		free(name);
		free(sym_to_free);
	}
}

void						print_arch_sym(t_file *file, int multiple_files, char *ar_name)
{
	t_arch				*tmp;
	t_arch				*arch_to_free;

	tmp = file->arch;
	arch_to_free = tmp;
	if (!file->is_fat)
	{
		if (ar_name)
			printf("\n%s(%s):\n", ar_name, file->name);
		else if (multiple_files)
			printf("\n%s:\n", file->name);
		print_symbols(tmp, tmp->name_int == ARCH_64);
		free(arch_to_free);
		return ;
	}
	while (tmp)
	{
		if (file->display_multiple_cpu > 1)
			print_filename_and_cpu(tmp, file->name);
		else if (ar_name)
			printf("\n%s(%s):\n", ar_name, file->name);
		else if (multiple_files)
			printf("\n%s:\n", file->name);
		print_symbols(tmp, tmp->name_int == ARCH_64);
		tmp = tmp->next;
		free(arch_to_free);
		arch_to_free = tmp;
	}
}
