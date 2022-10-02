NAME = cub3d

MAIN = srcs/cub3d.c
ENGINE = $(wildcard srcs/engine/*.c)
UTI = $(wildcard srcs/utils/*.c)

SRC = $(ENGINE) $(UTI) $(MAIN)
HDRS = $(wildcard incl/*.h)

OBJ = $(SRC:.c=.o)
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
	@gcc -g -Imlx -I ${HDRS} -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(PURPLE)$(SEP)"
	@echo "Compiling $(NAME)... $(YELLOW)"
	@(make -C ./mlx/mlxo/) 2> /dev/null
	@gcc -g $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled succesfully.$(PURPLE)"
	@echo "$(SEP)$(BLANK)"

all: $(NAME)

clean:
	@echo "$(RED)Cleaning..."
	@(${RM} $(OBJ))
	@make -C ./mlx/mlxo/ clean
	@echo "$(BLANK)"

clean2:
	@echo "$(RED)Cleaning..."
	@(${RM} $(NAME) ${OBJ})
	@echo "$(BLANK)"

fclean: clean
	@(${RM} $(NAME) ${OBJ})

re: clean2 $(NAME)

git:
	@git add $(SRC) mlx/ Makefile $(HDRS)
	git status

.PHONY: all clean fclean re git clean2
