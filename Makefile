NAME = cub3d

MAIN = srcs/cub3d.c
ENGINE = $(wildcard srcs/engine/*.c)
UTI = $(wildcard srcs/utils/*.c)

SRC = $(ENGINE) $(UTI) $(MAIN)
HDRS = $(wildcard incl/*.h)

OBJ = $(SRC:.c=.o)

RM = rm -rf

%.o: %.c
	gcc -Imlx -I ${HDRS} -c $< -o $@

$(NAME): $(OBJ)
	@(make -C ./mlx/mlxo/) 2> /dev/null
	@gcc $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "\033[92m$(NAME) compiled succesfully.\033[0m"


all: $(NAME)

clean:
	@${RM} $(OBJ)
	@make -C ./mlx/mlxo/ clean

clean2:
	@${RM} $(NAME) ${OBJ}

fclean: clean
	@${RM} $(NAME) ${OBJ}
	@make -C ./mlx/mlxo/ clean

re: clean2
	@make all

git:
	@git add $(SRC) mlx/ Makefile $(HDRS)
	git status

.PHONY: all clean fclean re git
