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

void						parse_32_segments(t_file *file, struct segment_command *sc, t_arch *arch)
{	
	uint32_t				i;
	struct section			*sect;

	i = -1;
	sect = (void*)sc + sizeof(struct segment_command);
	while (++i < sc->nsects)
	{
		arch->n_sect++;
		//printf("[%d] SEGNAME: [%s]\tSECTNAME: [%s]\n", arch->is_little_endian, sect[i].segname, sect[i].sectname);
		//if (arch->is_little_endian)
		//	swap_section_32(&sect[i]);
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
	while (++i < sc->nsects)
	{
		arch->n_sect++;
		//if (arch->is_little_endian)
		//	swap_section_64(&sect[i]);
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
