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

# define ARCH_32 1
# define ARCH_64 2
# define FAT 3
# define SWAP(x)		swap_endian((unsigned char*)&x, sizeof(x))

typedef struct			s_symbol
{
	uint64_t			value;
	uint8_t				type;
	uint8_t				section_index;
	char				type_char;
	char				*name;
	int					is_external;
	struct s_symbol		*next;
}						t_symbol;

typedef struct			s_arch
{
	int					name_int;
	char				*name_str;
	uint32_t			offset;
	t_symbol			*sym_head;
	char				sect_char[256];
	int					n_sect;
	int					is_little_endian;
	struct s_arch		*next;
}						t_arch;

typedef struct			s_file
{
	char				*name;
	void				*content;
	size_t				len;
	t_arch				*arch;
	int					is_little_endian;
	int					is_fat;
}						t_file;

unsigned char				*swap_endian(unsigned char *data, size_t n);

/*
**	FT_NM.C
*/
void					ft_nm(char *filename, int multiple_files);
void					dispatch_by_magic(t_file *file);

/*
**	HANDLE_FILE.C
*/
t_file					check_file(char *command, char *filename);

/*
**	HANDLE_HEADER.C
*/
void						handle_new_arch(t_file *file, uint32_t offset);
void						handle_32_header(t_file *file, uint32_t offset, t_arch *arch);
void						handle_64_header(t_file *file, uint32_t offset, t_arch *arch);
void						handle_fat_header(t_file *file);

/*
**	HANDLE_SEGMENT.C
*/
void						parse_32_segments(t_file *file, struct segment_command *sc, t_arch *arch);
void						parse_64_segments(t_file *file, struct segment_command_64 *sc, t_arch *arch, uint32_t offset);

/*
**	HANDLE_32_SYMBOL.C
*/
void						get_symbol_type_char_32(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol);
void						get_symbol_name_32(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol);
void						get_symbol_value_32(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol);
void						parse_symtable_32(t_file *file, struct symtab_command *sc, t_arch *arch);

/*
**	HANDLE_64_SYMBOL.C
*/
void						get_symbol_type_char_64(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol);
void						get_symbol_name_64(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol);
void						get_symbol_value_64(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol);
void						parse_symtable_64(t_file *file, struct symtab_command *sc, t_arch *arch);

/*
**	HANDLE_ERROR.C
*/
void					perror_nosuchfile(char *command, char *filename);
void					perror_fileerror(char *command, char *filename);
void					perror_maperror(char *command, char *filename);
void					perror_command(char *command);
void					perror_filename(char *filename);

/*
**	UTILS.C
*/
void					sort_symbols_by_name(t_arch *arch);
int							check_stab_32(t_file *file, uint32_t i, struct symtab_command *sc);
int							check_stab_64(t_file *file, uint32_t i, struct symtab_command *sc);
void						add_symbol_to_list(t_symbol **sym_head, t_symbol *symbol);
t_symbol					*new_symbol(void);
void						add_arch_to_list(t_file *file, t_arch *arch);
void					sort_arch_symbols(t_file *file);

void						swap_nlist_32(t_file *file, uint32_t offset);
void						swap_nlist_64(t_file *file, uint32_t offset);

#endif
