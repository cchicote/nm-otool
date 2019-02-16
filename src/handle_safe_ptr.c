/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_safe_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 18:53:43 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/11 18:53:50 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm_otool.h>

int							check_ptr(t_file *file, void *lc)
{
	struct load_command *load_co;
	void				*file_end;

	load_co = (struct load_command*)lc;
	file_end = file->content + file->len;
	return (lc <= file_end && (lc + load_co->cmdsize) <= file_end);
}

int							check_seg_nsect(uint32_t sect_size, uint32_t cmdsize, uint32_t nsects)
{
	return (sect_size * nsects <= cmdsize);
}

int							check_segment_32(t_file *file, uint32_t cmdsize, struct segment_command *seg, uint32_t seg_index)
{
	if (!check_seg_nsect(sizeof(struct section), cmdsize, seg->nsects))
	{
		perror_truncated_malformed_seg_nsect("ft_nm", file->name,
			"LC_SEGMENT", seg_index);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int							check_segment_64(t_file *file, uint32_t cmdsize, struct segment_command_64 *seg, uint32_t seg_index)
{
	if (!check_seg_nsect(sizeof(struct section_64), cmdsize, seg->nsects))
	{
		perror_truncated_malformed_seg_nsect("ft_nm", file->name,
			"LC_SEGMENT_64", seg_index);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
