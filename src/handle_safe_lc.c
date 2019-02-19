/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_safe_lc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 17:39:50 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/16 17:39:58 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							check_lc_end(void *lc_end, void *lc)
{
	return (lc <= lc_end);
}

int							check_lc_multiple(struct load_command *lc)
{
	return (lc->cmdsize % 4 == 0);
}

int							check_lc(t_file *file, void *lc, void *lc_end, uint32_t i)
{
	if (!check_lc_end(lc_end, lc))
	{
		perror_truncated_malformed_lc(file->command, file->name, i);
		return (EXIT_FAILURE);
	}
	if (!check_ptr(file, lc))
	{
		perror_truncated_malformed_file(file->command, file->name, i);
		return (EXIT_FAILURE);
	}
	if (!check_lc_multiple((struct load_command*)lc))
	{
		perror_truncated_malformed_multiple(file->command, file->name, i);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
