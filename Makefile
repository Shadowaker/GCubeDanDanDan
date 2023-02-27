NAME = cub3d
OS = $(shell uname)
TEXT = TEXT=1

MAIN = srcs/cub3d.c
ENGINE = $(wildcard srcs/engine/*.c) \
	$(wildcard srcs/engine/untextured/*.c) \
	$(wildcard srcs/engine/textured/*.c) \
	$(wildcard srcs/engine/hud/*.c)
UTI = $(wildcard srcs/utils/*.c)
MAPS = $(wildcard maps/*.cub)

SRC = $(ENGINE) $(UTI) $(MAIN) srcs/init.c srcs/keys.c srcs/moves.c
HDRS = incl/gcube.h
LIBS = $(wildcard incl/*.h)
SPRITES = $(wildcard srcs/sprites/Fireplace/*.xpm) \
	$(wildcard srcs/sprites/DeathEater/*.xpm) \
	$(wildcard srcs/sprites/hud/*.xpm)

OBJ = $(SRC:.c=.o)
ASS = gcc
CFLAGS = -Wall -Wextra -Werror -g -O3
RM = rm -rf

RED = "\\033[91m"
GREEN = "\\033[92m"
YELLOW = "\\033[93m"
BLUE = "\\033[94m"
PURPLE =  "\\033[95m"
CYAN = "\\033[96m"
BLANK = "\\033[0m"
SEP = "***********************************************************"

%.o: %.c
	@if [ $(OS) = "Darwin" ]; then\
		$(ASS) -g -Imlx -O3 -I ${HDRS} -c $< -o $@;\
	else\
		$(ASS) -g -I/usr/include -Imlx_linux -I ${HDRS} -c $< -o $@;\
	fi

$(NAME): $(OBJ)
	@echo "Trying to resolve OS..."
	@echo "$(PURPLE)$(SEP)"
	@echo "Compiling $(NAME)... $(YELLOW)\n\n"

	@if [ $(OS) = "Darwin" ]; then\
		make mac;\
	else\
		make linux;\
	fi

	@echo "$(GREEN)$(NAME) compiled succesfully.$(PURPLE)"
	@echo "$(SEP)$(BLANK)"

all: $(NAME)

linux:
	@echo "Compiling $(BLUE)Linux$(YELLOW) mlx...\n"
	@(make -C ./mlx_linux) 2> /dev/null
	@echo "\n\n"
	@gcc -g $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -D LIN=1 -o $(NAME)

mac:
	@echo "Compiling $(BLUE)Darwin$(YELLOW) mlx...\n"
	@(make -C ./mlx/mlxo/) 2> /dev/null
	@echo "\n\n"
	@$(ASS) $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@echo "$(RED)Cleaning..."
	@(${RM} $(OBJ))
	@make -C ./mlx/mlxo/ clean
	@echo "$(BLANK)"

clear: clean

clean2:
	@echo "$(RED)Cleaning..."
	@(${RM} $(NAME) ${OBJ})
	@echo "$(BLANK)"

fclean: clean
	@(${RM} $(NAME) ${OBJ})

re: clean2 $(NAME)

# GIT UTILITIES

git: fclean
	@git add $(SRC) mlx/ Makefile $(HDRS) $(MAPS) mlx_linux/ $(LIBS) $(SPRITES)
	git status

gcubepush:
	git push origin master

revert:
	@echo "$(YELLOW) This rule will revert every change to the last commit. $(BLANK)"
	@git reset
	@git checkout .
	@git clean -fdx
	@echo "$(GREEN) Done. $(BLANK)"

.SILENT: all linux mac
.PHONY: all clean fclean re git clean2 clear revert linux mac .SILENT
#da qui è passata alice
