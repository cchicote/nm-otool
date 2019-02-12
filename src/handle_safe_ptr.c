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

	load_co = (struct load_command*)lc;
	return (lc <= (file->content + file->len) && (lc + load_co->cmdsize) <= (file->content + file->len));
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
	if (!check_ptr(file, lc))
	{
		perror_truncated_malformed_file("ft_nm", file->name, i);
		return (EXIT_FAILURE);
	}
	if (!check_lc_end(lc_end, lc))
	{
		
		perror_truncated_malformed_lc("ft_nm", file->name, i);
		return (EXIT_FAILURE);
	}
	if (!check_lc_multiple((struct load_command*)lc))
	{
		perror_truncated_malformed_multiple("ft_nm", file->name, i);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
