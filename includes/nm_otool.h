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
# include <mach/machine.h>
# include <mach-o/ranlib.h>
# include <ar.h>
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
	cpu_type_t			cputype;
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
	int					display_multiple_cpu;
	void				*curr_arch;
	void				*curr_header_end;
}						t_file;

typedef struct			s_ar_header
{
	struct ar_hdr		*ar_header;
	char				long_name[20];
}						t_ar_header;

typedef struct			s_ar_symtab
{
	uint32_t			sym_offset;
	uint32_t			obj_offset;
}						t_ar_symtab;

/*
**	FT_NM.C
*/
int						ft_nm(char *filename, int multiple_files);
int					dispatch_by_magic(t_file *file);

/*
**	HANDLE_FILE.C
*/
t_file					check_file(char *command, char *filename);

/*
**	HANDLE_HEADER.C
*/
int							handle_new_arch(t_file *file, uint32_t offset);
int							handle_32_header(t_file *file, t_arch *arch);
int							handle_64_header(t_file *file, t_arch *arch);
int							handle_fat_header(t_file *file);

/*
**	HANDLE_SEGMENT.C
*/
int							parse_32_segments(t_file *file, struct segment_command *sc, t_arch *arch, uint32_t seg_offset);
int							parse_64_segments(t_file *file, struct segment_command_64 *sc, t_arch *arch, uint32_t seg_offset);

/*
**	HANDLE_32_SYMBOL.C
*/
int							check_stab_32(t_file *file, uint32_t i, struct symtab_command *sc, t_arch *arch);
void						get_symbol_type_char_32(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol, t_arch *arch);
void						get_symbol_name_32(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol, t_arch *arch);
void						get_symbol_value_32(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol, t_arch *arch);
void						parse_symtable_32(t_file *file, struct symtab_command *sc, t_arch *arch);

/*
**	HANDLE_64_SYMBOL.C
*/
int							check_stab_64(t_file *file, uint32_t i, struct symtab_command *sc, t_arch *arch);
void						get_symbol_type_char_64(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol, t_arch *arch);
void						get_symbol_name_64(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol, t_arch *arch);
void						get_symbol_value_64(t_file *file, uint32_t i, struct symtab_command *sc, t_symbol *symbol, t_arch *arch);
void						parse_symtable_64(t_file *file, struct symtab_command *sc, t_arch *arch);

/*
**	HANDLE_ERROR.C
*/
void					perror_nosuchfile(char *command, char *filename);
void					perror_fileerror(char *command, char *filename);
void					perror_maperror(char *command, char *filename);
void					perror_command(char *command);
void					perror_filename(char *filename);
void					perror_directory(char *command, char *filename);
void					perror_truncated_malformed_lc(char *command, char *filename, uint32_t failing_lc);
void					perror_truncated_malformed_file(char *command, char *filename, uint32_t failing_lc);
void					perror_truncated_malformed_multiple(char *command, char *filename, uint32_t failing_lc);
void					perror_truncated_malformed_sect_file(char *command, char *filename, uint32_t failing_sect, uint32_t failing_seg, char *segname);
void					perror_truncated_malformed_sect_header(char *command, char *filename, uint32_t failing_sect, uint32_t failing_seg, char *segname);
void					perror_truncated_malformed_seg_nsect(char *command, char *filename, char *segname, uint32_t failing_seg);

/*
**	UTILS.C
*/
void					sort_symbols_by_name(t_arch *arch);
void						add_symbol_to_list(t_symbol **sym_head, t_symbol *symbol);
t_symbol					*new_symbol(void);
void						add_arch_to_list(t_file *file, t_arch *arch);
void					sort_arch_symbols(t_file *file);

unsigned char				*swap_endian(unsigned char *data, size_t n);

void						swap_32_header(t_file *file, uint32_t offset);
void						swap_64_header(t_file *file, uint32_t offset);
void						swap_fat_header(t_file *file, uint32_t offset);
void						swap_fat_arch(t_file *file, uint32_t offset, uint32_t i);

void						swap_load_command(struct load_command *lc);
void						swap_nlist_32(t_file *file, t_arch *arch, uint32_t offset, uint32_t i);
void						swap_nlist_64(t_file *file, t_arch *arch, uint32_t offset, uint32_t i);
void						swap_32_segment_command(struct segment_command *sc);
void						swap_64_segment_command(struct segment_command_64 *sc);
void						swap_symtab_command(struct symtab_command *sc);
void						swap_section_32(struct section *sect);
void						swap_section_64(struct section_64 *sect_64);

int						handle_archive(t_file *file);
t_file					generate_file_from_archive(char *command, char *ar_name, void *hdr_ptr);
void					print_arch_sym(t_file *file, int multiple_files, char *ar_name);
uint32_t				get_name_size_from_ar_hdr(void *hdr_ptr);
uint32_t				get_file_size_from_ar_hdr(void *hdr_ptr);
int						check_ptr(t_file *file, void *lc);
int						check_lc(t_file *file, void *lc, void *lc_end, uint32_t i);
int						check_section_32(t_file *file, struct section sect, uint32_t sect_index, uint32_t seg_index);
int						check_section_64(t_file *file, struct section_64 sect, uint32_t sect_index, uint32_t seg_index);
int						check_segment_32(t_file *file, uint32_t cmdsize, struct segment_command *seg, uint32_t seg_index);
int						check_segment_64(t_file *file, uint32_t cmdsize, struct segment_command_64 *seg, uint32_t seg_index);
void					unmap_file(t_file *file);

#endif
