# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wescande <wescande@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/29 21:32:58 by wescande          #+#    #+#              #
#*   Updated: 2017/02/18 01:44:35 by wescande         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror

DELTA		=	$$(echo "$$(tput cols)-47"|bc)

LIBFT_DIR	=	libft/
LIBFT_LIB	=	$(LIBFT_DIR)libft.a
LIBFT_INC	=	$(LIBFT_DIR)includes/

SRC_DIR		=	srcs/
INC_DIR		=	includes/
OBJ_DIR		=	objs/

UNAME		=	$(shell uname)

SDL_DIR		=	SDL2-2.0.5
SDL_LIB		=	$(SDL_DIR)/build/.libs/libSDL2.a
SDL_INC		=	$(SDL_DIR)/include/

ifeq ($(UNAME), Darwin)
FLAG_SDL	=	-I/$(SDL_INC) $(SDL_LIB) -framework Cocoa -framework CoreAudio -framework AudioToolbox -framework ForceFeedback -framework CoreVideo -framework Carbon -framework IOKit -liconv
endif

ifeq ($(UNAME), Linux)
	FLAG_SDL	=	-I/$(SDL_INC) $(SDL_LIB) -lXext -lX11 -lm -ldl -pthread
endif

SRC_BASE	=	\
draw_minimap.c\
draw_screen.c\
draw_sprite.c\
ft_wolf.c\
wolf_audio.c\
wolf_calc.c\
wolf_error.c\
wolf_floor.c\
wolf_hit_box.c\
wolf_input.c\
wolf_jump.c\
wolf_loadmap.c\
wolf_move.c\
wolf_ray.c\
wolf_skybox.c\
wolf_sprite.c\
wolf_window.c

SRCS		=	$(addprefix $(SRC_DIR), $(SRC_BASE))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC_BASE:.c=.o))
NB			=	$(words $(SRC_BASE))
INDEX		=	0

all : $(SDL_LIB)
	@make -j -C $(LIBFT_DIR)
	@make -j $(NAME)

$(NAME):		$(SDL_LIB) $(LIBFT_LIB) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) \
		-I $(INC_DIR) \
		-I $(LIBFT_INC) $(LIBFT_LIB) \
		$(FLAG_SDL) \
		$(FLAGS)
	@printf "\r\033[48;5;15;38;5;25m✅ MAKE $(NAME)\033[0m\033[K\n"

$(SDL_DIR):
	@printf "\r\033[38;5;11m⌛ EXTRACT %10.10s\033[0m\033[K" $(SDL_DIR)
	@$(shell tar xzf .$(SDL_DIR).tar.gz)
	@printf "\r\033[48;5;15;38;5;25m✅ EXTRACT $(SDL_DIR)\033[0m\033[K\n"

$(SDL_LIB): $(SDL_DIR)
	@printf "\r\033[38;5;11m⌛ CONFIGURE %10.10s" $(SDL_DIR)
	@cd $(SDL_DIR) && ./configure >/dev/null
	@printf "\r\033[48;5;15;38;5;25m✅ CONFIGURE $(SDL_DIR)\033[0m\033[K\n"
	@printf "\r\033[38;5;11m⌛ MAKE %10.10s" $(SDL_DIR)
	@cd $(SDL_DIR) && make >/dev/null 2>/dev/null
	@printf "\r\033[48;5;15;38;5;25m✅ MAKE $(SDL_DIR)\033[0m\033[K\n"

$(LIBFT_LIB):
	@make -j -C $(LIBFT_DIR)

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $(OBJS))

$(OBJ_DIR)%.o :	$(SRC_DIR)%.c | $(OBJ_DIR)
	@$(eval DONE=$(shell echo $$(($(INDEX)*20/$(NB)))))
	@$(eval PERCENT=$(shell echo $$(($(INDEX)*100/$(NB)))))
	@$(eval COLOR=$(shell echo $$(($(PERCENT)%35+196))))
	@$(eval TO_DO=$(shell echo $$((20-$(INDEX)*20/$(NB)))))
	@printf "\r\033[38;5;11m⌛ MAKE %10.10s : %2d%% \033[48;5;%dm%*s\033[0m%*s\033[48;5;255m \033[0m \033[38;5;11m %*s\033[0m\033[K" $(NAME) $(PERCENT) $(COLOR) $(DONE) "" $(TO_DO) "" $(DELTA) "$@"
	@$(CC) $(FLAGS) -MMD -c $< -o $@\
		-I $(INC_DIR)\
		-I $(SDL_INC)\
		-I $(LIBFT_INC)
	@$(eval INDEX=$(shell echo $$(($(INDEX)+1))))

clean:			cleanlib
	@rm -rf $(OBJ_DIR)
	@printf "\r\033[01;38;5;202m✖ clean $(NAME).\033[0m\033[K\n"

cleanlib:
	@make -C $(LIBFT_DIR) clean

fcleanpart:			clean fcleanlib
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m❌ fclean $(NAME).\033[0m\033[K\n"

fclean:			clean fcleanlib fcleansdl
	@rm -f $(NAME)
	@printf "\r\033[38;5;196m❌ fclean $(NAME).\033[0m\033[K\n"

cleansdl:
	@if [ -f $(SDL_DIR)/Makefile ] ; \
	then \
		make -C $(SDL_DIR) clean; \
		printf "\r\033[01;38;5;202m✖ clean $(SDL_DIR).\033[0m\033[K\n"; \
	else \
		printf "\r\033[01;38;5;202m✖ Nothing to be done: $(SDL_DIR).\033[0m\033[K\n"; \
	fi;

fcleansdl:		cleansdl
	@if [ -e $(SDL_DIR) ] ; \
	then \
		rm -rf $(SDL_DIR); \
		printf "\r\033[38;5;196m❌ fclean $(SDL_DIR).\033[0m\033[K\n"; \
	else \
		printf "\r\033[38;5;196m❌ Nothing to be done: $(SDL_DIR).\033[0m\033[K\n"; \
	fi;


fcleanlib:		cleanlib
	@make -C $(LIBFT_DIR) fclean

re:				fcleanpart all

relib:			fcleanlib $(LIBFT_LIB) $(SDL_LIB)

.PHONY :		fclean clean re relib cleanlib fcleanlib resdl cleansdl fcleansdl fcleanpart

-include $(OBJS:.o=.d)
