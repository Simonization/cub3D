# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 13:52:09 by agoldber          #+#    #+#              #
#    Updated: 2025/04/10 18:01:36 by agoldber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#BASE

NAME			=	cub3d
INCLUDES		=	includes
MLX_DIR			=	includes/minilibx-linux
SRCS_DIR 		=	src/
SRCS_BONUS_DIR	=	src_bonus/
OBJS_DIR		=	obj/
CC				=	cc
C_FLAGS			=	-g -Ofast -Wall -Werror -Wextra -I${INCLUDES} -I${MLX_DIR}
LIBFT			=	libft.a
MLX_LIB			=	-lmlx_Linux -L${MLX_DIR} -I${MLX_DIR} -lXext -lX11 -lm -lz
RM				=	rm -rf
MAKEFLAGS		+=	--no-print-directory
C_FLAGS			+=	${READLINE_FLAG}

#COLORS

BGREEN			=	\033[1;32m
BBLUE			=	\033[1;34m
BCYAN			=	\033[1;36m
BPURPLE			=	\033[1;35m
BWHITE			=	\033[1;37m
BYELLOW			=	\033[1;33m
BRED			=	\033[1;31m
PASTEL_PINK		=	\033[38;5;210m
PASTEL_PURPLE	=	\033[38;5;183m
PASTEL_BLUE		=	\033[38;5;111m
COLOR_END		=	\033[0m

#SOURCES

FILES			=	main draw_ray move hooks init
# FILES			=	main draw_ray move hooks init_bonus

SRCS			=	${addprefix ${SRCS_DIR}, ${addsuffix .c, ${FILES}}}
OBJS			=	${addprefix ${OBJS_DIR}, ${addsuffix .o, ${FILES}}}

#PROGRESS BAR
TOTAL_FILES		=	$(words $(FILES))

# ---------------------------------------------------------------------------- #

OBJSF			=	.cache_exists

all: check

check: ${NAME}
	@echo "${BGREEN}\nEverything up to date${COLOR_END}";

${NAME}: ${LIBFT} ${OBJS}
			@${CC} ${OBJS} ${LIBFT} ${MLX_LIB} -o ${NAME}
			@echo "\n${BGREEN}Cub3D compiled!${COLOR_END}"

${LIBFT}:
			@make -C libft/
			@mv libft/libft.a .
			@make clean -C libft/
			
${OBJS_DIR}%.o : ${SRCS_DIR}%.c | ${OBJSF}
			@mkdir -p $(dir $@)
			@${CC} ${C_FLAGS} -c $< -o $@
			@PROGRESS=$$(echo "$$(find ${OBJS_DIR} -type f | wc -l | tr -d ' ') * 100 / ${TOTAL_FILES}" | bc); \
			BAR=$$(seq -s "▇" 0 $$((PROGRESS / 2)) | tr -d '[:digit:]'); \
			SPACES=$$(seq -s " " 0 $$((50 - PROGRESS / 2)) | tr -d '[:digit:]'); \
			CURRENT_FILES=$$(find ${OBJS_DIR} -type f | wc -l | tr -d ' '); \
			printf "\r${BBLUE}Compiling: [$$BAR$$SPACES] $$PROGRESS%% ($$CURRENT_FILES/${TOTAL_FILES})${COLOR_END}"

${OBJSF}:
			@mkdir -p ${OBJS_DIR}

clean:
			@${RM} ${OBJS_DIR}
			@${RM} ${OBJSF}
			@echo "${BCYAN}.o files cleaned!${COLOR_END}"

fclean:	clean
			@${RM} ${NAME}
			@${RM} ${LIBFT}
			@echo "${BBLUE}.a files cleaned!${COLOR_END}"

re:		fclean all

.PHONY:	all clean fclean re check