NAME = cub3d
OS = $(shell uname)

MAIN = srcs/cub3d.c
ENGINE = $(wildcard srcs/engine/*.c)
TEXT = $(wildcard srcs/engine/textures/*.c)
UTI = $(wildcard srcs/utils/*.c)
MAPS = $(wildcard maps/*.cub)

SRC = $(ENGINE) $(UTI) $(MAIN) $(TEXT)
HDRS = incl/gcube.h

OBJ = $(SRC:.c=.o)
ASS = gcc -Wall -Wextra -Werror
RM = rm -rf

RED = "\\033[91m"
GREEN = "\\033[92m"
YELLOW = "\\033[93m"
BLUE = "\\033[94m"
PURPLE =  "\\033[95m"
CYAN = "\\033[96m"
BLANK = "\\033[0m"
SEP = "***********************************************************"

.SILENT: all linux mac

%.o: %.c
	@if [ $(OS) = "Darwin" ]; then\
		gcc -g -Imlx -I ${HDRS} -c $< -o $@;\
	else\
		gcc -g -I/usr/include -Imlx_linux -O3 -I ${HDRS} -c $< -o $@;\
	fi

$(NAME): $(OBJ)
	@echo "Trying to resolve OS..."
	@echo "$(PURPLE)$(SEP)"
	@echo "Compiling $(NAME)... $(YELLOW)"

	@if [ $(OS) = "Darwin" ]; then\
		make mac;\
	else\
		make linux;\
	fi

	@echo "$(GREEN)$(NAME) compiled succesfully.$(PURPLE)"
	@echo "$(SEP)$(BLANK)"

all: $(NAME)

linux:
	@(make -C ./mlx_linux) 2> /dev/null
	@gcc -g $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -D LIN=1 -o $(NAME)

mac:
	@(make -C ./mlx/mlxo/) 2> /dev/null
	@gcc -g $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	@echo "$(RED)Cleaning..."
	@(${RM} $(OBJ))
	@make -C ./mlx/mlxo/ clean
	@make -C ./mlx_linux clean
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
	@git add $(SRC) mlx/ Makefile $(HDRS) $(MAPS) mlx_linux/
	git status

gcubepush:
	git push origin master

revert:
	@echo "$(YELLOW) This rule will revert every change to the last commit. $(BLANK)"
	@git reset
	@git checkout .
	@git clean -fdx
	@echo "$(GREEN) Done. $(BLANK)"

.PHONY: all clean fclean re git clean2 clear revert linux mac
