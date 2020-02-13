.PHONY: all clean fclean re

NAME = ft_ssl

WFLAGS = -Wall -Wextra -Werror

SRC_PATH = ./srcs/
INC_PATH = ./inc/
OBJ_PATH = ./obj/

SRC = $(addprefix $(SRC_PATH),$(N_SRCS))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = -I $(INC_PATH)  
HEADERS := $(addprefix $(INC_PATH)/, malloc.h)

OBJ_NAME = $(N_SRCS:.c=.o)

N_SRCS =	ft_alloc.c		\

all : $(NAME)

$(NAME):	$(OBJ)
				@gcc $(INC) $(OBJ) -o $(NAME)
				@printf "\033[34;5m Malloc OK ! \n\033[0m"

$(OBJ_PATH)%.o:	$(SRC_PATH)%.c $(HEADERS)
					@mkdir -p $(OBJ_PATH)
					@gcc -c $(INC) $(WFLAGS) -o $@ $<
					@printf "\033[44m \033[0m"

clean :
				@rm -rf $(OBJ_PATH)

fclean : 	clean
				@rm -rf $(NAME)

re : fclean clean all
