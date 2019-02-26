/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:10:26 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/16 18:10:34 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						swap_load_command(struct load_command *lc)
{
	swap_endian((unsigned char*)&lc->cmd, sizeof(lc->cmd));
	swap_endian((unsigned char*)&lc->cmdsize, sizeof(lc->cmdsize));
}

void						swap_32_seg_command(struct segment_command *sc)
{
	swap_endian((unsigned char*)&sc->segname, sizeof(sc->segname));
	swap_endian((unsigned char*)&sc->vmaddr, sizeof(sc->vmaddr));
	swap_endian((unsigned char*)&sc->vmsize, sizeof(sc->vmsize));
	swap_endian((unsigned char*)&sc->fileoff, sizeof(sc->fileoff));
	swap_endian((unsigned char*)&sc->filesize, sizeof(sc->filesize));
	swap_endian((unsigned char*)&sc->maxprot, sizeof(sc->maxprot));
	swap_endian((unsigned char*)&sc->initprot, sizeof(sc->initprot));
	swap_endian((unsigned char*)&sc->nsects, sizeof(sc->nsects));
	swap_endian((unsigned char*)&sc->flags, sizeof(sc->flags));
}

void						swap_64_seg_command(struct segment_command_64 *sc)
{
	swap_endian((unsigned char*)&sc->segname, sizeof(sc->segname));
	swap_endian((unsigned char*)&sc->vmaddr, sizeof(sc->vmaddr));
	swap_endian((unsigned char*)&sc->vmsize, sizeof(sc->vmsize));
	swap_endian((unsigned char*)&sc->fileoff, sizeof(sc->fileoff));
	swap_endian((unsigned char*)&sc->filesize, sizeof(sc->filesize));
	swap_endian((unsigned char*)&sc->maxprot, sizeof(sc->maxprot));
	swap_endian((unsigned char*)&sc->initprot, sizeof(sc->initprot));
	swap_endian((unsigned char*)&sc->nsects, sizeof(sc->nsects));
	swap_endian((unsigned char*)&sc->flags, sizeof(sc->flags));
}

void						swap_symtab_command(struct symtab_command *sc)
{
	swap_endian((unsigned char*)&sc->symoff, sizeof(sc->symoff));
	swap_endian((unsigned char*)&sc->nsyms, sizeof(sc->nsyms));
	swap_endian((unsigned char*)&sc->stroff, sizeof(sc->stroff));
	swap_endian((unsigned char*)&sc->strsize, sizeof(sc->strsize));
}
