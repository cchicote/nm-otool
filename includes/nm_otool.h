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

/*
** Options: LC = LowerCase / UC = UpperCase
** LCU = -u meanwhile UCU = -U
*/
# define LCG				0
# define LCP				1
# define LCR				2
# define LCU				3
# define LCJ				4
# define UCU				5
# define ARCH_32			1
# define ARCH_64			2
# define PPC				4
# define FAT				3

typedef struct				s_symbol
{
	uint64_t				value;
	uint8_t					type;
	uint8_t					section_index;
	char					type_char;
	char					*name;
	int						is_external;
	struct s_symbol			*next;
}							t_symbol;

typedef struct				s_arch
{
	int						name_int;
	char					*name_str;
	uint32_t				offset;
	t_symbol				*sym_head;
	char					sect_char[256];
	int						n_sect;
	int						is_little_endian;
	cpu_type_t				cputype;
	void					*t_sect_addr;
	void					*addr;
	struct s_arch			*next;
}							t_arch;

typedef struct				s_file
{
	char					*name;
	void					*content;
	char					*command;
	size_t					len;
	t_arch					*arch;
	uint32_t				curr_filetype;
	int						is_little_endian;
	int						is_fat;
	int						display_multiple_cpu;
	void					*curr_arch;
	void					*curr_header_end;
	char					*options;
}							t_file;

typedef struct				s_ar_header
{
	struct ar_hdr			*ar_header;
	char					long_name[20];
}							t_ar_header;

typedef struct				s_ar_symtab
{
	uint32_t				sym_offset;
	uint32_t				obj_offset;
}							t_ar_symtab;

/*
**							FT_NM.C
*/
int							ft_nm(char *filename, char *options,
								int multiple_files);

/*
**							FT_OTOOL.C
*/
int							ft_otool(char *filename);

/*
**							HANDLE_32_HEADER.C
*/
int							handle_nm_32_header(t_file *file, t_arch *arch);
int							handle_otool_32_header(t_file *file, t_arch *arch);
void						update_32_header_values(t_file *file, t_arch *arch,
								struct mach_header *header);
void						lc_is_32_symtab(t_file *file, t_arch *arch,
								struct load_command *lc);
int							lc_is_32_segment(t_file *file, t_arch *arch,
								struct load_command *lc, uint32_t i);

/*
**							HANDLE_32_SYMBOL.C
*/
int							check_stab_32(struct nlist array);
void						get_symbol_type_char_32(t_symbol *symbol,
								struct nlist array);
void						get_symbol_name_32(t_file *file, t_symbol *symbol,
								struct nlist array, char *stringtable);
void						get_symbol_value_32(t_symbol *symbol,
								struct nlist array);
void						parse_symtable_32(t_file *file,
								struct symtab_command *sc, t_arch *arch);

/*
**							HANDLE_64_HEADER.C
*/
int							handle_nm_64_header(t_file *file, t_arch *arch);
int							handle_otool_64_header(t_file *file, t_arch *arch);
void						update_64_header_values(t_file *file, t_arch *arch,
								struct mach_header_64 *header);
void						lc_is_64_symtab(t_file *file, t_arch *arch,
								struct load_command *lc);
int							lc_is_64_segment(t_file *file, t_arch *arch,
								struct load_command *lc, uint32_t i);

/*
**							HANDLE_64_SYMBOL.C
*/
int							check_stab_64(struct nlist_64 array);
void						get_symbol_type_char_64(t_symbol *symbol,
								struct nlist_64 array);
void						get_symbol_name_64(t_file *file, t_symbol *symbol,
								struct nlist_64 array, char *stringtable);
void						get_symbol_value_64(t_symbol *symbol,
								struct nlist_64 array);
void						parse_symtable_64(t_file *file,
								struct symtab_command *sc, t_arch *arch);

/*
**							HANDLE_ARCH.C
*/
int							handle_new_arch(t_file *file, uint32_t offset);
int							handle_32_arch(t_file *file, t_arch *arch,
								uint32_t magic, uint32_t offset);
int							handle_64_arch(t_file *file, t_arch *arch,
								uint32_t magic, uint32_t offset);

/*
**							HANDLE_ARCHIVE.C
*/
uint32_t					parse_ar_symtab_max_offset(t_file *file);
int							handle_archive(t_file *file);
void						print_archive_name_otool(t_file *file);
uint32_t					get_file_size_from_ar_hdr(void *hdr_ptr);
uint32_t					get_name_size_from_ar_hdr(void *hdr_ptr);

/*
**							HANDLE_DISPATCH.C
*/
int							dispatch_by_magic(t_file *file);

/*
**							HANDLE_ERROR_TRUNCATED.c
*/
void						perror_truncated_malformed_lc(char *command,
								char *filename, uint32_t failing_lc);
void						perror_truncated_malformed_file(char *command,
								char *filename, uint32_t failing_lc);
void						perror_truncated_malformed_multiple(char *command,
								char *filename, uint32_t failing_lc);
void						perror_truncated_malformed_seg_nsect(char *command,
								char *filename, char *segname,
								uint32_t failing_seg);
void						perror_truncated_malformed_seg_eof(char *command,
								char *filename, char *segname,
								uint32_t failing_seg);

/*
**							HANDLE_ERROR_UTILS.C
*/
void						perror_command(char *command);
void						perror_filename(char *filename);
void						perror_missing_file(char *command);
void						perror_invalid_file(char *command, char *filename);

/*
**							HANDLE_ERROR.C
*/
void						perror_nosuchfile(char *command, char *filename);
void						perror_fileerror(char *command, char *filename);
void						perror_maperror(char *command, char *filename);
void						perror_directory(char *command, char *filename);
t_file						perror_return(t_file file, char *command,
								char *filename,
								void (*perror_func)(char *cmd, char *fnm));

/*
**							HANDLE_FAT_HEADER.C
*/
int							handle_fat_header(t_file *file);
cpu_type_t					get_current_cpu_type(void);
int							check_valid_cpu_type(cpu_type_t cputype);

/*
**							HANDLE_FILE.C
*/
t_file						check_file(char *command, char *filename);
int							unmap_file_failure(t_file *file, int exit_value);
void						unmap_file(t_file *file);
int							generate_file_from_archive_nm(char *command,
								char *ar_name, void *hdr_ptr, char *options);
int							generate_file_from_archive_otool(char *command,
								char *ar_name, void *hdr_ptr, char *options);

/*
**							HANDLE_LITTLE_ENDIAN.C
*/
unsigned char				*swap_endian(unsigned char *data, size_t size);
void						swap_nlist_32(t_file *file, t_arch *arch,
								uint32_t offset, uint32_t i);
void						swap_nlist_64(t_file *file, t_arch *arch,
								uint32_t offset, uint32_t i);
void						swap_section_32(struct section *sect);
void						swap_section_64(struct section_64 *sect_64);

/*
**							HANDLE_NM_ERROR_TRUNCATED.C
*/
void						perror_nm_trunc_malf_sect_file(char *filename,
								uint32_t failing_sect, uint32_t failing_seg,
								char *segname);
void						perror_nm_trunc_malf_sect_header(char *filename,
								uint32_t failing_sect, uint32_t failing_seg,
								char *segname);

/*
**							HANDLE_OPTIONS.C
*/
int							parse_options(char *options, char *str);
char						*init_options(void);
void						perror_wrong_option(char *option);

/*
**							HANDLE_OTOOL_ERROR_TRUNCATED.C
*/
void						perror_otool_trunc_malf_sect_file(char *filename,
								uint32_t failing_sect, uint32_t failing_seg,
								char *segname);
void						perror_otool_trunc_malf_sect_header(char *filename,
								uint32_t failing_sect, uint32_t failing_seg,
								char *segname);

/*
**							HANDLE_SAFE_LC.C
*/
int							check_lc(t_file *file, void *lc, void *lc_end,
								uint32_t i);
int							check_lc_multiple(struct load_command *lc);
int							check_lc_end(void *lc_end, void *lc);

/*
**							HANDLE_SAFE_PTR.C
*/
int							check_ptr(t_file *file, void *lc);
int							check_seg_nsect(uint32_t sect_size,
								uint32_t cmdsize, uint32_t nsects);
int							check_segment_32(t_file *file,
								uint32_t cmdsize, struct segment_command *seg,
								uint32_t seg_index);
int							check_segment_64(t_file *file, uint32_t cmdsize,
								struct segment_command_64 *seg,
								uint32_t seg_index);
int							check_eof(t_file *file,
								uint64_t fileoff, uint64_t filesize);

/*
**							HANDLE_SAFE_SECT.C
*/
int							check_sect_offset_file(t_file *file,
								uint32_t offset);
int							check_sect_offset_header(t_file *file,
								uint32_t offset);
int							check_section_32(t_file *file, struct section sect,
								uint32_t sect_index, uint32_t seg_index);
int							check_section_64(t_file *file,
								struct section_64 sect,
								uint32_t sect_index, uint32_t seg_index);
int							is_filetype_dylib(uint32_t filetype);

/*
**							HANDLE_SEGMENT.C
*/
int							parse_32_segments(t_file *file,
								struct segment_command *sc, t_arch *arch,
								uint32_t seg_offset);
int							parse_64_segments(t_file *file,
								struct segment_command_64 *sc, t_arch *arch,
								uint32_t seg_offset);
int							get_64_text_sect_addr(t_file *file,
								struct segment_command_64 *sc, t_arch *arch,
								uint32_t seg_offset);
int							get_32_text_sect_addr(t_file *file,
								struct segment_command *sc, t_arch *arch,
								uint32_t seg_offset);

/*
**							HANDLE_SORTING.C
*/
int							cmp_null_values(char *a, char *b);
t_symbol					*sorted_merge(t_symbol *a, t_symbol *b,
								char reverse);
void						front_back_split(t_symbol *source,
								t_symbol **front_ref, t_symbol **back_ref);
void						merge_sort(t_symbol **head_ref, char reverse);
void						sort_arch_symbols(t_file *file);

/*
**							LLUTOA_BASE.C
*/
char						*fill_with_char(char *src, char to_fill, int size);
size_t						get_number_len(uint64_t nb, int base);
char						*ft_llutoa_base(uint64_t nb, int base);
void						print_char_filled(char *src, char to_fill,
								int size);

/*
**							PRINT_NM.C
*/
void						print_sym_value(uint64_t value, char to_fill,
								int is_64);
void						print_symbol(t_symbol *symbol, char *name,
								char *options, int is_64);
void						print_filename(char *filename, char *ar_name,
								int multiple_files, int is_nm);
void						print_cputype(cpu_type_t cputype);
void						print_filename_and_cpu(t_file *file, t_arch *arch,
								char *filename);

/*
**							PRINT_OTOOL.C
*/
void						print_otool_address(uint64_t addr, int size);
void						print_hex_char(char value);
void						print_hex_num(uint32_t value);

/*
**							PRINT_SYMBOLS.C
*/
void						print_filename_and_cpu(t_file *file, t_arch *arch,
								char *filename);
void						print_symbols(t_arch *arch, char *options,
								int is_64);
void						print_arch_sym(t_file *file, int multiple_files,
								char *ar_name);

/*
**							PRINT_T_SECT.C
*/
void						print_t_sect(t_file *file, char *ar_name);
void						print_name_and_sect(t_file *file, t_arch *arch,
								char *ar_name);
void						print_hexdump_32(t_arch *arch);
void						print_hexdump_64(t_arch *arch);
void						print_hexdump_ppc(t_arch *arch);

/*
**							SWAP_COMMAND.C
*/
void						swap_load_command(struct load_command *lc);
void						swap_32_seg_command(struct segment_command *sc);
void						swap_64_seg_command(struct segment_command_64 *sc);
void						swap_symtab_command(struct symtab_command *sc);

/*
**							SWAP_HEADER.C
*/
void						swap_32_header(t_file *file, uint32_t offset);
void						swap_64_header(t_file *file, uint32_t offset);
void						swap_fat_header(t_file *file, uint32_t offset);
void						swap_fat_arch(t_file *file, uint32_t offset,
								uint32_t i);

/*
**							UTILS.C
*/
void						add_symbol_to_list(t_symbol **sym_head,
								t_symbol *symbol);
t_symbol					*new_symbol(void);
void						add_arch_to_list(t_file *file, t_arch *arch);

#endif
