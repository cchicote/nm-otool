/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:12:40 by cchicote          #+#    #+#             */
/*   Updated: 2019/01/22 18:12:50 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						swap_section_32(t_file *file, uint32_t offset)
{
	struct section			*section;

	section = file->content + offset;
	SWAP(section->sectname);
	SWAP(section->segname);
	SWAP(section->addr);
	SWAP(section->size);
	SWAP(section->offset);
	SWAP(section->align);
	SWAP(section->reloff);
	SWAP(section->nreloc);
	SWAP(section->flags);
	SWAP(section->reserved1);
	SWAP(section->reserved2);
}

void						swap_section_64(t_file *file, uint32_t offset)
{
	struct section_64		*section_64;

	section_64 = file->content + offset;
	SWAP(section_64->sectname);
	SWAP(section_64->segname);
	SWAP(section_64->addr);
	SWAP(section_64->size);
	SWAP(section_64->offset);
	SWAP(section_64->align);
	SWAP(section_64->reloff);
	SWAP(section_64->nreloc);
	SWAP(section_64->flags);
	SWAP(section_64->reserved1);
	SWAP(section_64->reserved2);
	SWAP(section_64->reserved3);
}

void						parse_32_segments(t_file *file, struct segment_command *sc, t_arch *arch)
{	
	uint32_t				i;
	struct section			*sect;

	i = -1;
	sect = (void*)sc + sizeof(struct segment_command);
	if (arch->is_little_endian)
		swap_section_32(file, (uint32_t)((void*)sect - file->content + arch->offset));
	while (++i < sc->nsects)
	{
		arch->n_sect++;
		if (ft_strncmp(sect[i].segname, SEG_TEXT, 16) == 0
			&& ft_strncmp(sect[i].sectname, SECT_TEXT, 16) == 0)
			arch->sect_char[arch->n_sect] = 't';
		else if (ft_strncmp(sect[i].segname, SEG_DATA, 16) == 0
			&& ft_strncmp(sect[i].sectname, SECT_DATA, 16) == 0)
			arch->sect_char[arch->n_sect] = 'd';
		else if (ft_strncmp(sect[i].segname, SEG_DATA, 16) == 0
			&& ft_strncmp(sect[i].sectname, SECT_BSS, 16) == 0)
			arch->sect_char[arch->n_sect] = 'b';
		else
			arch->sect_char[arch->n_sect] = 's';
	}
}

void						parse_64_segments(t_file *file, struct segment_command_64 *sc, t_arch *arch)
{	
	uint32_t				i;
	struct section_64		*sect;

	i = -1;
	sect = (void*)sc + sizeof(struct segment_command_64);
	if (arch->is_little_endian)
		swap_section_64(file, (uint32_t)((void*)sect - file->content + arch->offset));
	while (++i < sc->nsects)
	{
		arch->n_sect++;
		if (ft_strncmp(sect[i].segname, SEG_TEXT, 16) == 0
			&& ft_strncmp(sect[i].sectname, SECT_TEXT, 16) == 0)
			arch->sect_char[arch->n_sect] = 't';
		else if (ft_strncmp(sect[i].segname, SEG_DATA, 16) == 0
			&& ft_strncmp(sect[i].sectname, SECT_DATA, 16) == 0)
			arch->sect_char[arch->n_sect] = 'd';
		else if (ft_strncmp(sect[i].segname, SEG_DATA, 16) == 0
			&& ft_strncmp(sect[i].sectname, SECT_BSS, 16) == 0)
			arch->sect_char[arch->n_sect] = 'b';
		else
			arch->sect_char[arch->n_sect] = 's';
	}
}
