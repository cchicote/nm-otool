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

typedef struct			s_file
{
	char				*name;
	void				*content;
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

typedef struct			s_arch
{
	int					name_int;
	char				*name_str;
	t_symbol			*sym_head;
}						t_arch;

typedef struct			s_fat
{
	t_arch				*arch_head;
}						t_fat;

/*
**	FT_NM.C
*/
void					ft_nm(char *filename, int multiple_files);
uint32_t				dispatch_by_magic(void *content, t_symbol **sym_head);

/*
**	HANDLE_FILE.C
*/
t_file					check_file(char *command, char *filename);

/*
**	HANDLE_HEADER.C
*/
struct section				*handle_32_header(t_symbol **sym_head, void *content, uint32_t nsect, int need_swap);
struct section_64			*handle_64_header(t_symbol **sym_head, void *content, uint32_t nsect, int need_swap);
struct section				*handle_fat_header(t_symbol **sym_head, void *content, int need_swap);
uint64_t					swap_endian(uint64_t x, int need_swap);

/*
**	HANDLE_SEGMENT.C
*/
struct section				*parse_32_segments(struct segment_command *sc, uint32_t n_sect, int need_swap);
struct section_64			*parse_64_segments(struct segment_command_64 *sc, uint32_t n_sect, int need_swap);

/*
**	HANDLE_32_SYMBOL.C
*/
char						get_char_by_section_32(void *content, uint32_t n_sect, int need_swap);
void						get_symbol_type_char_32(void *content, uint32_t i, struct symtab_command *sc, t_symbol *symbol, int need_swap);
void						get_symbol_name_32(void *content, uint32_t i, struct symtab_command *sc, t_symbol *symbol, int need_swap);
void						get_symbol_value_32(void *content, uint32_t i, struct symtab_command *sc, t_symbol *symbol, int need_swap);
void						parse_symtable_32(t_symbol **sym_head, void *content, struct symtab_command *sc, int need_swap);

/*
**	HANDLE_64_SYMBOL.C
*/
char						get_char_by_section_64(void *content, uint32_t n_sect, int need_swap);
void						get_symbol_type_char_64(void *content, uint32_t i, struct symtab_command *sc, t_symbol *symbol, int need_swap);
void						get_symbol_name_64(void *content, uint32_t i, struct symtab_command *sc, t_symbol *symbol, int need_swap);
void						get_symbol_value_64(void *content, uint32_t i, struct symtab_command *sc, t_symbol *symbol, int need_swap);
void						parse_symtable_64(t_symbol **sym_head, void *content, struct symtab_command *sc, int need_swap);

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
void					sort_symbols_by_name(t_symbol **sym_head);
int							check_stab_32(void *content, uint32_t i, struct symtab_command *sc, int need_swap);
int							check_stab_64(void *content, uint32_t i, struct symtab_command *sc, int need_swap);
void						add_symbol_to_list(t_symbol **sym_head, t_symbol *symbol);
t_symbol					*new_symbol(void);

#endif
