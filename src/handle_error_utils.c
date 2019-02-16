/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 17:33:11 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/16 17:33:19 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void					perror_command(char *command)
{
	ft_putstr(command);
	ft_putstr(": ");
}

void					perror_filename(char *filename)
{
	ft_putstr(filename);
	ft_putstr(": ");
}
