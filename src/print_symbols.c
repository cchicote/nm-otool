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

void						print_symbols(t_arch *arch, char *options,
								int is_64)
{
	t_symbol				*tmp;
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
		print_symbol(tmp, name, options, is_64);
		sym_to_free = tmp;
		tmp = tmp->next;
		free(name);
		free(sym_to_free);
	}
}

void						print_arch_sym(t_file *file, int multiple_files,
								char *ar_name)
{
	t_arch				*tmp;
	t_arch				*arch_to_free;

	tmp = file->arch;
	arch_to_free = tmp;
	if (!file->is_fat)
	{
		print_filename(file->name, ar_name, multiple_files, TRUE);
		print_symbols(tmp, file->options, tmp->name_int == ARCH_64);
		free(arch_to_free);
		return ;
	}
	while (tmp)
	{
		if (file->display_multiple_cpu > 1)
			print_filename_and_cpu(file, tmp, file->name);
		else
			print_filename(file->name, ar_name, multiple_files, TRUE);
		print_symbols(tmp, file->options, tmp->name_int == ARCH_64);
		tmp = tmp->next;
		free(arch_to_free);
		arch_to_free = tmp;
	}
}
