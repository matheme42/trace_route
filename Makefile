BLUE=\033[0;38;5;123m
LIGHT_PINK = \033[0;38;5;200m
PINK = \033[0;38;5;198m
DARK_BLUE = \033[1;38;5;110m
GREEN = \033[1;32;111m
LIGHT_GREEN = \033[1;38;5;121m
LIGHT_RED = \033[0;38;5;110m
FLASH_GREEN = \033[33;32m
WHITE_BOLD = \033[37m

# nom de l'executable
NAME = ft_traceroute

#sources path
SRC_PATH		= srcs

#objects path
OBJ_PATH		= obj

#includes
INC_PATH		= includes
HEADER			= $(INC_PATH)/error.h $(INC_PATH)/ft_traceroute.h

# sources
NAME_SRC		=	main.c dnslookup.c send.c receive.c error.c socket.c ft.c ft_option.c

# objects
NAME_OBJ		= $(addprefix $(OBJ_PATH)/,$(NAME_SRC:.c=.o))

#compilateur + flags
CFLAGS		=  -Wall -Wextra -Werror


all : $(NAME)

$(NAME) : $(NAME_OBJ)
	@$(CC) $(CFLAGS) $^ -o $@ -lm
	@echo "	\033[2K\r$(DARK_BLUE)$(NAME):	$(GREEN)loaded\033[0m"
	@sudo setcap cap_net_raw=pe $(NAME)
	@echo "	\033[2K\r$(DARK_BLUE)$(NAME):	$(LIGHT_GREEN)autorized\033[0m"


$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEADER)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) -I $(INC_PATH) -c $< -o $@ -lm
	@printf "	\033[2K\r$(BLUE)$< $(GREEN)compiled\033[0m"

clean:
	@rm -f $(NAME_OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "	\033[2K\r$(DARK_BLUE)objects:	$(LIGHT_PINK)compiled\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "	\033[2K\r$(DARK_BLUE)$(NAME):	$(PINK)removing\033[0m"

re: fclean all

.PHONY: all clean fclean re
