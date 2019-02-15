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

int						check_ptr(t_file *file, void *lc)
{
	struct load_command *load_co;
	void				*file_end;

	load_co = (struct load_command*)lc;
	file_end = file->content + file->len;
	return (lc <= file_end && (lc + load_co->cmdsize) <= file_end);
}

int						check_lc_end(void *lc_end, void *lc)
{
	return (lc <= lc_end);
}

int						check_lc_multiple(struct load_command *lc)
{
	return (lc->cmdsize % 4 == 0);
}

int						check_lc(t_file *file, void *lc, void *lc_end, uint32_t i)
{
	if (!check_lc_end(lc_end, lc))
	{
		perror_truncated_malformed_lc("ft_nm", file->name, i);
		return (EXIT_FAILURE);
	}
	if (!check_ptr(file, lc))
	{
		perror_truncated_malformed_file("ft_nm", file->name, i);
		return (EXIT_FAILURE);
	}
	if (!check_lc_multiple((struct load_command*)lc))
	{
		perror_truncated_malformed_multiple("ft_nm", file->name, i);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int						check_sect_offset_file(t_file *file, uint32_t offset)
{
	return (file->curr_arch + offset <= file->content + file->len);
}

int						check_sect_offset_header(t_file *file, uint32_t offset)
{
	return (file->curr_arch + offset >= file->curr_header_end);
}

int						check_section_32(t_file *file, struct section sect, uint32_t sect_index, uint32_t seg_index)
{
	if (sect.flags & S_ZEROFILL)
		return (EXIT_SUCCESS);
	if (!check_sect_offset_file(file, sect.offset))
	{
		perror_truncated_malformed_sect_file("ft_nm",
			file->name, sect_index, seg_index, "LC_SEGMENT");
		return (EXIT_FAILURE);
	}
	if (!check_sect_offset_header(file, sect.offset))
	{
  		perror_truncated_malformed_sect_header("ft_nm",
		  	file->name, sect_index, seg_index, "LC_SEGMENT");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int						check_section_64(t_file *file, struct section_64 sect, uint32_t sect_index, uint32_t seg_index)
{
	if (sect.flags & S_ZEROFILL)
		return (EXIT_SUCCESS);
	if (!check_sect_offset_file(file, sect.offset))
	{
		perror_truncated_malformed_sect_file("ft_nm",
			file->name, sect_index, seg_index, "LC_SEGMENT_64");
		return (EXIT_FAILURE);
	}
	if (!check_sect_offset_header(file, sect.offset))
	{
		perror_truncated_malformed_sect_header("ft_nm",
			file->name, sect_index, seg_index, "LC_SEGMENT_64");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int						check_seg_nsect(uint32_t sect_size, uint32_t cmdsize, uint32_t nsects)
{
	return (sect_size * nsects <= cmdsize);
}

int						check_segment_32(t_file *file, uint32_t cmdsize, struct segment_command *seg, uint32_t seg_index)
{
	if (!check_seg_nsect(sizeof(struct section), cmdsize, seg->nsects))
	{
		perror_truncated_malformed_seg_nsect("ft_nm", file->name,
			"LC_SEGMENT", seg_index);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int						check_segment_64(t_file *file, uint32_t cmdsize, struct segment_command_64 *seg, uint32_t seg_index)
{
	if (!check_seg_nsect(sizeof(struct section_64), cmdsize, seg->nsects))
	{
		perror_truncated_malformed_seg_nsect("ft_nm", file->name,
			"LC_SEGMENT_64", seg_index);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
