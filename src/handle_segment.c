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

int							get_64_text_sect_addr(t_file *file,
								struct segment_command_64 *sc, t_arch *arch,
								uint32_t seg_offset)
{
	uint32_t				i;
	struct section_64		*sect;

	i = -1;
	sect = (void*)sc + sizeof(struct segment_command_64);
	while (++i < sc->nsects)
	{
		if (arch->is_little_endian)
			swap_section_64(&sect[i]);
		if (check_section_64(file, sect[i], i, seg_offset) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		arch->n_sect++;
		if (ft_strncmp(sect[i].segname, SEG_TEXT, 16) == 0
			&& ft_strncmp(sect[i].sectname, SECT_TEXT, 16) == 0)
		{
			arch->t_sect_addr = sect;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}

int							get_32_text_sect_addr(t_file *file,
								struct segment_command *sc, t_arch *arch,
								uint32_t seg_offset)
{
	uint32_t				i;
	struct section			*sect;

	i = -1;
	sect = (void*)sc + sizeof(struct segment_command);
	while (++i < sc->nsects)
	{
		if (arch->is_little_endian)
			swap_section_32(&sect[i]);
		if (check_section_32(file, sect[i], i, seg_offset) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		arch->n_sect++;
		if (ft_strncmp(sect[i].segname, SEG_TEXT, 16) == 0
			&& ft_strncmp(sect[i].sectname, SECT_TEXT, 16) == 0)
		{
			arch->t_sect_addr = sect;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}

int							parse_32_segments(t_file *file,
								struct segment_command *sc, t_arch *arch,
								uint32_t seg_offset)
{
	uint32_t				i;
	struct section			*sect;

	i = -1;
	sect = (void*)sc + sizeof(struct segment_command);
	while (++i < sc->nsects)
	{
		if (arch->is_little_endian)
			swap_section_32(&sect[i]);
		if (check_section_32(file, sect[i], i, seg_offset) == EXIT_FAILURE)
			return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}

int							parse_64_segments(t_file *file,
								struct segment_command_64 *sc, t_arch *arch,
								uint32_t seg_offset)
{
	uint32_t				i;
	struct section_64		*sect;

	i = -1;
	sect = (void*)sc + sizeof(struct segment_command_64);
	while (++i < sc->nsects)
	{
		if (arch->is_little_endian)
			swap_section_64(&sect[i]);
		if (check_section_64(file, sect[i], i, seg_offset) == EXIT_FAILURE)
			return (EXIT_FAILURE);
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
	return (EXIT_SUCCESS);
}
