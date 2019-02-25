/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_little_endian.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 17:47:58 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/01 17:48:07 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

unsigned char				*swap_endian(unsigned char *data, size_t size)
{
	size_t					i;
	size_t					half;
	unsigned char			swap;

	i = 0;
	half = size / 2;
	while (i < half)
	{
		swap = data[i];
		data[i] = data[size - i - 1];
		data[size - i - 1] = swap;
		++i;
	}
	return (data);
}

void						swap_section_32(struct section *sect)
{
	swap_endian((unsigned char*)&sect->addr, sizeof(sect->addr));
	swap_endian((unsigned char*)&sect->size, sizeof(sect->size));
	swap_endian((unsigned char*)&sect->offset, sizeof(sect->offset));
	swap_endian((unsigned char*)&sect->align, sizeof(sect->align));
	swap_endian((unsigned char*)&sect->reloff, sizeof(sect->reloff));
	swap_endian((unsigned char*)&sect->nreloc, sizeof(sect->nreloc));
	swap_endian((unsigned char*)&sect->flags, sizeof(sect->flags));
	swap_endian((unsigned char*)&sect->reserved1, sizeof(sect->reserved1));
	swap_endian((unsigned char*)&sect->reserved2, sizeof(sect->reserved2));
}

void						swap_section_64(struct section_64 *sect_64)
{
	swap_endian((unsigned char*)&sect_64->addr, sizeof(sect_64->addr));
	swap_endian((unsigned char*)&sect_64->size, sizeof(sect_64->size));
	swap_endian((unsigned char*)&sect_64->offset, sizeof(sect_64->offset));
	swap_endian((unsigned char*)&sect_64->align, sizeof(sect_64->align));
	swap_endian((unsigned char*)&sect_64->reloff, sizeof(sect_64->reloff));
	swap_endian((unsigned char*)&sect_64->nreloc, sizeof(sect_64->nreloc));
	swap_endian((unsigned char*)&sect_64->flags, sizeof(sect_64->flags));
	swap_endian((unsigned char*)&sect_64->reserved1, sizeof(sect_64->reserved1));
	swap_endian((unsigned char*)&sect_64->reserved2, sizeof(sect_64->reserved2));
	swap_endian((unsigned char*)&sect_64->reserved3, sizeof(sect_64->reserved3));
}

void						swap_nlist_32(t_file *file, t_arch *arch, uint32_t offset, uint32_t i)
{
	struct nlist			*nlist;

	nlist = file->content + arch->offset + offset;
	swap_endian((unsigned char*)&nlist[i].n_un.n_strx, sizeof(nlist[i].n_un.n_strx));
	swap_endian((unsigned char*)&nlist[i].n_type, sizeof(nlist[i].n_type));
	swap_endian((unsigned char*)&nlist[i].n_sect, sizeof(nlist[i].n_sect));
	swap_endian((unsigned char*)&nlist[i].n_desc, sizeof(nlist[i].n_desc));
	swap_endian((unsigned char*)&nlist[i].n_value, sizeof(nlist[i].n_value));
}

void						swap_nlist_64(t_file *file, t_arch *arch, uint32_t offset, uint32_t i)
{
	struct nlist_64			*nlist_64;

	nlist_64 = file->content + arch->offset + offset;
	swap_endian((unsigned char*)&nlist_64[i].n_un.n_strx, sizeof(nlist_64[i].n_un.n_strx));
	swap_endian((unsigned char*)&nlist_64[i].n_type, sizeof(nlist_64[i].n_type));
	swap_endian((unsigned char*)&nlist_64[i].n_sect, sizeof(nlist_64[i].n_sect));
	swap_endian((unsigned char*)&nlist_64[i].n_desc, sizeof(nlist_64[i].n_desc));
	swap_endian((unsigned char*)&nlist_64[i].n_value, sizeof(nlist_64[i].n_value));
}
