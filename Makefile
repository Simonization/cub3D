# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agoldber < agoldber@student.s19.be >       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/04 13:52:09 by agoldber          #+#    #+#              #
#    Updated: 2025/05/19 17:05:27 by agoldber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#BASE

NAME			=	cub3d
NAME_BONUS		=	cub3d_bonus
INCLUDES		=	includes
MLX_DIR			=	includes/minilibx-linux
SRCS_DIR 		=	src/
PARSE_DIR		=	parse/
DRAW_RAY_DIR	=	draw_ray/
MOVE_DIR		=	movement/
MINIMAP_DIR		=	minimap/
SRCS_BONUS_DIR	=	src_bonus/
OBJS_DIR		=	obj/
OBJS_BONUS_DIR	=	obj_bonus/
CC				=	cc
C_FLAGS			=	-Ofast -Wall -Werror -Wextra -I${INCLUDES} -I${MLX_DIR} -g
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
DRAW_RAY_FILES	=	draw_ray draw_ray_utils
MOVE_FILES		=	direction move
PARSE_FILES		=	parse_basis parse_gen_cub_file parse_map parse_map_utils map_validation RGB_validation rgb_utils texture_validation process_textures
P_BONUS_FILES	=	parse_basis_bonus parse_gen_cub_file_bonus parse_map_bonus parse_map_utils_bonus map_validation_bonus RGB_validation_bonus rgb_utils_bonus texture_validation_bonus process_textures_bonus
RAY_BONUS_FILES	=	draw_ray_bonus draw_ray_utils_bonus
MINIMAP_FILES	=	minimap_bonus minimap_shape_bonus
MOVE_BONUS_FILES=	move_bonus vision_bonus direction_bonus

DRAW_RAY		=	${addprefix ${DRAW_RAY_DIR}, ${DRAW_RAY_FILES}}
MOVE			=	${addprefix ${MOVE_DIR}, ${MOVE_FILES}}
PARSE			=	${addprefix ${PARSE_DIR}, ${PARSE_FILES}}
PARSE_BONUS		=	${addprefix ${PARSE_DIR}, ${P_BONUS_FILES}}
DRAW_RAY_BONUS	=	${addprefix ${DRAW_RAY_DIR}, ${RAY_BONUS_FILES}}
MINIMAP			=	${addprefix ${MINIMAP_DIR}, ${MINIMAP_FILES}}
MOVE_BONUS		=	${addprefix ${MOVE_DIR}, ${MOVE_BONUS_FILES}}

FILES			=	main hooks init init_player_orientation utils ${DRAW_RAY} ${MOVE} ${PARSE}
FILES_BONUS		=	main_bonus hooks_bonus init_bonus player_init utils_bonus weapon_bonus weapon_init draw_xpm ${DRAW_RAY_BONUS} ${MOVE_BONUS} ${MINIMAP} ${PARSE_BONUS}

SRCS			=	${addprefix ${SRCS_DIR}, ${addsuffix .c, ${FILES}}}
SRCS_BONUS		=	${addprefix ${SRCS_BONUS_DIR}, ${addsuffix .c, ${FILES_BONUS}}}
OBJS			=	${addprefix ${OBJS_DIR}, ${addsuffix .o, ${FILES}}}
OBJS_BONUS		=	${addprefix ${OBJS_BONUS_DIR}, ${addsuffix .o, ${FILES_BONUS}}}

#PROGRESS BAR
TOTAL_FILES		=	$(words $(FILES))
TOT_FILES_BONUS	=	$(words $(FILES_BONUS))

# ---------------------------------------------------------------------------- #

OBJSF			=	.cache_exists
OBJSF_BONUS		=	.cache_exists_bonus

all: check

check: ${NAME}
			@echo -e "${BGREEN}\nEverything up to date${COLOR_END}";

${NAME}: ${LIBFT} ${OBJS}
			@${CC} ${OBJS} ${LIBFT} ${MLX_LIB} -o ${NAME}
			@echo -e "\n${BGREEN}Cub3D compiled!${COLOR_END}"

${LIBFT}:
			@make -C libft/
			@mv libft/libft.a .
			@make clean -C libft/
			
${OBJS_DIR}%.o : ${SRCS_DIR}%.c | ${OBJSF}
			@mkdir -p $(dir $@)
			@${CC} ${C_FLAGS} -c $< -o $@
			@PROGRESS=$$(echo -e "$$(find ${OBJS_DIR} -type f | wc -l | tr -d ' ') * 100 / ${TOTAL_FILES}" | bc); \
			BAR=$$(seq -s "▇" 0 $$((PROGRESS / 2)) | tr -d '[:digit:]'); \
			SPACES=$$(seq -s " " 0 $$((50 - PROGRESS / 2)) | tr -d '[:digit:]'); \
			CURRENT_FILES=$$(find ${OBJS_DIR} -type f | wc -l | tr -d ' '); \
			printf "\r${BBLUE}Compiling: [$$BAR$$SPACES] $$PROGRESS%% ($$CURRENT_FILES/${TOTAL_FILES})${COLOR_END}"

${OBJSF}:
			@mkdir -p ${OBJS_DIR}

clean:
			@${RM} ${OBJS_DIR}
			@${RM} ${OBJSF}
			@${RM} ${OBJS_BONUS_DIR}
			@${RM} ${OBJSF_BONUS}
			@echo -e "${BCYAN}.o files cleaned!${COLOR_END}"

fclean:	clean
			@${RM} ${NAME}
			@${RM} ${NAME_BONUS}
			@${RM} ${LIBFT}
			@echo -e "${BBLUE}.a files cleaned!${COLOR_END}"

re:		fclean all

bonus: ${NAME_BONUS}
			@echo -e "${BGREEN}\nEverything up to date${COLOR_END}";

${NAME_BONUS}: ${LIBFT} ${OBJS_BONUS}
			@${CC} ${OBJS_BONUS} ${LIBFT} ${MLX_LIB} -o ${NAME_BONUS}
			@echo -e "\n${BGREEN}Bonus compiled!${COLOR_END}"
			
${OBJS_BONUS_DIR}%.o : ${SRCS_BONUS_DIR}%.c | ${OBJSF_BONUS}
			@mkdir -p $(dir $@)
			@${CC} ${C_FLAGS} -c $< -o $@
			@PROGRESS=$$(echo -e "$$(find ${OBJS_BONUS_DIR} -type f | wc -l | tr -d ' ') * 100 / ${TOT_FILES_BONUS}" | bc); \
			BAR=$$(seq -s "▇" 0 $$((PROGRESS / 2)) | tr -d '[:digit:]'); \
			SPACES=$$(seq -s " " 0 $$((50 - PROGRESS / 2)) | tr -d '[:digit:]'); \
			CURRENT_FILES=$$(find ${OBJS_BONUS_DIR} -type f | wc -l | tr -d ' '); \
			printf "\r${BBLUE}Compiling: [$$BAR$$SPACES] $$PROGRESS%% ($$CURRENT_FILES/${TOT_FILES_BONUS})${COLOR_END}"

${OBJSF_BONUS}:
			@mkdir -p ${OBJS_BONUS_DIR}

re_bonus : fclean bonus

.PHONY:	all clean fclean re check bonus re_bonus
