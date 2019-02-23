/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:31:05 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/21 18:31:09 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void                        print_sym_value(uint64_t value, char to_fill, int is_64)
{
	int						size;
	char					*str_value;

	size = is_64 ? 16 : 8;
	if (!value)
		print_char_filled("", to_fill, size);
	else
	{
		str_value = ft_llutoa_base(value, 16);
		print_char_filled(str_value, to_fill, size);
		free(str_value);
	}
}

void						print_symbol(t_symbol *symbol, char *name, char *options, int is_64)
{
	if (options[LCG] && !ft_isupper(symbol->type_char))
		return ;
	if (options[LCU] && ft_toupper(symbol->type_char) != 'U')
		return ;
	if (options[UCU] && ft_toupper(symbol->type_char) == 'U')
		return ;
	if (!options[LCJ] && !options[LCU])
	{
		if (ft_toupper(symbol->type_char) != 'U')
			print_sym_value(symbol->value, '0', is_64);
		else
			print_sym_value(symbol->value, ' ', is_64);	
		ft_putchar(' ');
		ft_putchar(symbol->type_char);
		ft_putchar(' ');
	}
	ft_putendl(name);
}

void						print_filename(char *filename, char *ar_name, int multiple_files, int is_nm)
{
	if (!ar_name && !multiple_files)
		return ;
	if (is_nm)
		ft_putchar('\n');
	if (ar_name)
	{	
		ft_putstr(ar_name);
		ft_putchar('(');
		ft_putstr(filename);
		ft_putchar(')');
	}
	else if (multiple_files)
		ft_putstr(filename);
	ft_putendl(":");
}

void						print_cputype(cpu_type_t cputype)
{
	if (cputype == CPU_TYPE_X86_64)
		ft_putstr("x86_64");
	else if (cputype == CPU_TYPE_I386)
		ft_putstr("i386");
	else if (cputype == CPU_TYPE_POWERPC)
		ft_putstr("ppc");
	else if (cputype == CPU_TYPE_POWERPC64)
		ft_putstr("ppc64");
	else if (cputype == CPU_TYPE_ARM)
		ft_putstr("arm");
	else if (cputype == CPU_TYPE_ARM64)
		ft_putstr("arm64");
	else if (cputype == CPU_TYPE_SPARC)
		ft_putstr("sparc");
	else if (cputype == CPU_TYPE_MC98000)
		ft_putstr("mc98000");
	else
		ft_putstr("unknown");
}

void						print_filename_and_cpu(t_file *file, t_arch *arch, char *filename)
{
	if (ft_strcmp(file->command, "ft_otool") == 0)
	{
		ft_putstr(filename);
		ft_putstr(" (architecture ");
	}
	else
	{
		ft_putchar('\n');
		ft_putstr(filename);
		ft_putstr(" (for architecture ");
	}
	print_cputype(arch->cputype);
	ft_putendl("):");
}