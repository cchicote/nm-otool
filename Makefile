# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchicote <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/11 16:29:33 by cchicote          #+#    #+#              #
#    Updated: 2018/12/20 18:35:01 by cchicote         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM_NAME 		= ft_nm
OTOOL_NAME 		= ft_otool
CC 				= gcc
CFLAGS 			= -Wall -Wextra -O1 -g -fsanitize=address #-Werror
LFLAGS 			= -lft
INC 			= -I$(INCLUDE_PATH)

INCLUDE_PATH 	= ./includes
LIBFT_PATH 		= ./libft
SRC_PATH 		= ./src/
OBJ_PATH 		= ./obj/

UTILS_SRCS		= handle_file.c \
					handle_archive.c \
					handle_arch.c \
					handle_error.c \
					handle_error_utils.c \
					handle_error_truncated.c \
					handle_safe_ptr.c \
					handle_safe_lc.c \
					handle_safe_sect.c \
					handle_nm_error_truncated.c \
					handle_otool_error_truncated.c \
					handle_little_endian.c \
					swap_header.c \
					swap_command.c \
					handle_dispatch.c \
					handle_32_header.c \
					handle_64_header.c \
					handle_fat_header.c \
					handle_segment.c \
					handle_32_symbol.c \
					handle_64_symbol.c \
					print_symbols.c \
					print_t_sect.c \
					handle_sorting.c \
					utils.c
NM_SRCS			= ft_nm.c \
					$(UTILS_SRCS)
OTOOL_SRCS		= ft_otool.c \
					$(UTILS_SRCS)
LIBFT 			= $(LIBFT_PATH)/libft.a

NM_OBJ 			= $(addprefix $(OBJ_PATH), $(NM_SRCS:.c=.o))
OTOOL_OBJ 		= $(addprefix $(OBJ_PATH), $(OTOOL_SRCS:.c=.o))


all: $(NM_NAME) $(OTOOL_NAME)

$(LIBFT):
	@ echo "Compiling libft"
	@ make -sC $(LIBFT_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@ echo "Compiling objects"
	@ mkdir -p $(OBJ_PATH)
	@ $(CC) $(CFLAGS) $(INC) -o $@ -c $<

$(NM_NAME): $(LIBFT) $(NM_OBJ)
	@ $(CC) $(CFLAGS) -o $@ $(NM_OBJ) -L $(LIBFT_PATH) $(LFLAGS)
	@ echo "$(NM_NAME) compiled"

$(OTOOL_NAME): $(LIBFT) $(OTOOL_OBJ)
	@ $(CC) $(CFLAGS) -o $@ $(OTOOL_OBJ) -L $(LIBFT_PATH) $(LFLAGS)
	@ echo "$(OTOOL_NAME) compiled"

clean:
	@ echo "Cleaning .o files"
	@ /bin/rm -Rf $(OBJ_PATH)
	@ echo "Cleaning libft"
	@ make clean -sC $(LIBFT_PATH)

fclean: clean
	@ echo "Cleaning $(NM_NAME)"
	@ /bin/rm -f $(NM_NAME)
	@ echo "Cleaning $(OTOOL_NAME)"
	@ /bin/rm -f $(OTOOL_NAME)
	@ echo "Fcleaning libft"
	@ make fclean -sC $(LIBFT_PATH)


re: fclean all

.PHONY : all clean fclean re
