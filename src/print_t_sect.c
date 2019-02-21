/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_t_sect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 16:27:56 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/18 16:28:03 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						print_hexdump_ppc(t_arch *arch)
{
	uint32_t				i;
	struct section			*sect;
	uint32_t				*content;

	sect = arch->t_sect_addr;
	content = (arch->addr + sect->offset);
	sect->size /= 4;
	i = 0;
	ft_putendl("Contents of (__TEXT,__text) section");
	while (i < sect->size)
	{
		if (i % 4 == 0)
		{
			print_otool_address(sect->addr, 8);
			sect->addr += 16;
		}
		if (arch->is_little_endian)
			SWAP(content[i]);
		print_hex_num(content[i]);
		i++;
		if (i % 4 == 0)
			ft_putchar('\n');
	}
	if (i % 4 != 0)
		ft_putchar('\n');
}

void						print_hexdump_32(t_arch *arch)
{
	uint32_t				i;
	struct section			*sect;
	char					*content;

	sect = arch->t_sect_addr;
	content = arch->addr;
	i = 0;
	ft_putendl("Contents of (__TEXT,__text) section");
	while (i < sect->size)
	{
		if (i % 16 == 0)
		{
			print_otool_address(sect->addr, 8);
			sect->addr += 16;
		}
		if (arch->is_little_endian)
			SWAP(content[sect->offset + i]);
		print_hex_char(content[sect->offset + i]);
		i++;
		if (i % 16 == 0)
			ft_putchar('\n');
	}
	if (i % 16 != 0)
		ft_putchar('\n');
}

void						print_hexdump_64(t_arch *arch)
{
	uint64_t				i;
	struct section_64		*sect;
	char					*content;

	sect = arch->t_sect_addr;
	content = arch->addr;
	i = 0;
	ft_putendl("Contents of (__TEXT,__text) section");
	while (i < sect->size)
	{
		if (i % 16 == 0)
		{
			print_otool_address(sect->addr, 16);
			sect->addr += 16;
		}
		if (arch->is_little_endian)
			SWAP(content[sect->offset + i]);
		print_hex_char(content[sect->offset + i]);
		i++;
		if (i % 16 == 0)
			ft_putchar('\n');
	}
	if (i % 16 != 0)
		ft_putchar('\n');
}

void						print_name_and_sect(t_file *file, t_arch *arch, char *ar_name)
{
	if (!file->is_fat)
		print_filename(file->name, ar_name, TRUE, FALSE);
	else
	{
		if (file->display_multiple_cpu > 1)
			print_filename_and_cpu(file, arch, file->name);
		else
			print_filename(file->name, ar_name, TRUE, FALSE);
	}
	if (arch->name_int == ARCH_64)
		print_hexdump_64(arch);
	else if (arch->name_int == ARCH_32 && arch->cputype == CPU_TYPE_POWERPC)
		print_hexdump_ppc(arch);
	else if (arch->name_int == ARCH_32)
		print_hexdump_32(arch);
}

void						print_t_sect(t_file *file, char *ar_name)
{
	t_arch				*tmp;
	t_arch				*arch_to_free;

	tmp = file->arch;
	arch_to_free = tmp;
	if (!file->is_fat)
	{
		print_name_and_sect(file, tmp, ar_name);
		free(arch_to_free);
		return ;
	}
	while (tmp)
	{
		print_name_and_sect(file, tmp, ar_name);
		tmp = tmp->next;
		free(arch_to_free);
		arch_to_free = tmp;
	}
}