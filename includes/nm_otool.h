/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm-otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 18:30:59 by cchicote          #+#    #+#             */
/*   Updated: 2018/12/20 18:34:47 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>
# include <mach-o/nlist.h>
# include <stdio.h>

typedef struct			s_file
{
	char				*name;
	char				*content;
	size_t				len;
}						t_file;

typedef struct			s_symbol
{
	uint64_t			value;
	uint8_t				type;
	uint8_t				section_index;
	char				type_char;
	char				*name;
	struct s_symbol		*next;
}						t_symbol;


/*
**	FT_NM.C
*/
void					print_symbols(t_symbol **sym_head);
void					ft_nm(char *filename);

/*
**	HANDLE_FILE.C
*/
t_file					check_file(char *command, char *filename);

/*
**	HANDLE_HEADER.C
*/
void					print_symtable_32(uint32_t nsyms, uint32_t symoff, uint32_t stroff, char *content);
void					print_symtable_64(t_symbol **sym_head, uint32_t nsyms, uint32_t symoff, uint32_t stroff, char *content);
void					handle_32_header(t_symbol **sym_head, char *content);
void					handle_64_header(t_symbol **sym_head, char *content);

/*
**	HANDLE_ERROR.C
*/
void					perror_nosuchfile(char *command, char *filename);
void					perror_fileerror(char *command, char *filename);
void					perror_maperror(char *command, char *filename);
void					perror_command(char *command);
void					perror_filename(char *filename);


#endif
