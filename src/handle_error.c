/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:32:17 by cchicote          #+#    #+#             */
/*   Updated: 2019/01/10 15:32:23 by cchicote         ###   ########.fr       */
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

void					perror_nosuchfile(char *command, char *filename)
{
    perror_command(command);
    perror_filename(filename);
    ft_putendl("No such file or directory.");
}

void					perror_fileerror(char *command, char *filename)
{
    perror_command(command);
    perror_filename(filename);
	ft_putendl("The file was not recognized as a valid object file.");
}

void					perror_maperror(char *command, char *filename)
{
	perror_command(command);
    perror_filename(filename);
	ft_putendl("Mapping failed.");
}