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
	SWAP(lc->cmd);
	SWAP(lc->cmdsize);
}

void						swap_32_segment_command(struct segment_command *sc)
{
	SWAP(sc->segname);
	SWAP(sc->vmaddr);
	SWAP(sc->vmsize);
	SWAP(sc->fileoff);
	SWAP(sc->filesize);
	SWAP(sc->maxprot);
	SWAP(sc->initprot);
	SWAP(sc->nsects);
	SWAP(sc->flags);
}

void						swap_64_segment_command(struct segment_command_64 *sc)
{
	SWAP(sc->segname);
	SWAP(sc->vmaddr);
	SWAP(sc->vmsize);
	SWAP(sc->fileoff);
	SWAP(sc->filesize);
	SWAP(sc->maxprot);
	SWAP(sc->initprot);
	SWAP(sc->nsects);
	SWAP(sc->flags);
}

void						swap_symtab_command(struct symtab_command *sc)
{
	SWAP(sc->symoff);
	SWAP(sc->nsyms);
	SWAP(sc->stroff);
	SWAP(sc->strsize);
}
