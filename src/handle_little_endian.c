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

unsigned char				*swap_endian(unsigned char *data, size_t n)
{
	size_t					i;
	size_t					half;
	unsigned char			swap;

	i = 0;
	half = n / 2;
	while (i < half)
	{
		swap = data[i];
		data[i] = data[n - i - 1];
		data[n - i - 1] = swap;
		++i;
	}
	return (data);
}

void						swap_section_32(struct section *sect)
{
	SWAP(sect->addr);
	SWAP(sect->size);
	SWAP(sect->offset);
	SWAP(sect->align);
	SWAP(sect->reloff);
	SWAP(sect->nreloc);
	SWAP(sect->flags);
	SWAP(sect->reserved1);
	SWAP(sect->reserved2);
}

void						swap_section_64(struct section_64 *sect_64)
{
	SWAP(sect_64->addr);
	SWAP(sect_64->size);
	SWAP(sect_64->offset);
	SWAP(sect_64->align);
	SWAP(sect_64->reloff);
	SWAP(sect_64->nreloc);
	SWAP(sect_64->flags);
	SWAP(sect_64->reserved1);
	SWAP(sect_64->reserved2);
	SWAP(sect_64->reserved3);
}

void						swap_nlist_32(t_file *file, t_arch *arch, uint32_t offset, uint32_t i)
{
	struct nlist			*nlist;

	nlist = file->content + arch->offset + offset;
	SWAP(nlist[i].n_un.n_strx);
	SWAP(nlist[i].n_type);
	SWAP(nlist[i].n_sect);
	SWAP(nlist[i].n_desc);
	SWAP(nlist[i].n_value);
}

void						swap_nlist_64(t_file *file, t_arch *arch, uint32_t offset, uint32_t i)
{
	struct nlist_64			*nlist_64;

	nlist_64 = file->content + arch->offset + offset;
	SWAP(nlist_64[i].n_un.n_strx);
	SWAP(nlist_64[i].n_type);
	SWAP(nlist_64[i].n_sect);
	SWAP(nlist_64[i].n_desc);
	SWAP(nlist_64[i].n_value);
}
