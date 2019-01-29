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

struct section				*parse_32_segments(struct segment_command *sc, uint32_t n_sect, int need_swap)
{	
	uint32_t				i;
	static int				n_sect_counter = 0;
	struct section			*sect;

	i = -1;
	sect = (void*)sc + sizeof(struct segment_command);
	while (++i < swap_endian(sc->nsects, need_swap))
	{
		n_sect_counter++;
		if (n_sect_counter == (int)n_sect)
		{
			n_sect_counter = 0;
			return (&sect[i]);
		}
	}
	return (NULL);
}

struct section_64			*parse_64_segments(struct segment_command_64 *sc, uint32_t n_sect, int need_swap)
{	
	uint32_t				i;
	static int				n_sect_counter = 0;
	struct section_64		*sect;

	i = -1;
	sect = (void*)sc + sizeof(struct segment_command_64);
	while (++i < swap_endian(sc->nsects, need_swap))
	{
		n_sect_counter++;
		if (n_sect_counter == (int)n_sect)
		{
			n_sect_counter = 0;
			return (&sect[i]);
		}
	}
	return (NULL);
}