.PHONY: all clean fclean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = ft_irc
SERVER = server
CLIENT = client

PATH_OBJ = ./obj/
PATH_SRC = ./src/
PATH_INC = ./includes/
PATH_SERVEUR = serveur_files/
PATH_CLIENT = client_files/
PATH_SHARED= shared/

HEADER = $(PATH_INC)$(NAME).h

#******************************************************************************#
#                              SHARED                                          #
#******************************************************************************#

PATH_OBJ_SHARED = $(PATH_OBJ)$(PATH_SHARED)
PATH_SRC_SHARED = $(PATH_SRC)$(PATH_SHARED)

FILES_SHARED = 

OBJ_SHARED = $(addprefix $(PATH_OBJ_SHARED), $(addsuffix .o , $(FILES_SHARED)))
SRC_SHARED = $(addprefix $(PATH_SRC_SHARED), $(addsuffix .c , $(FILES_SHARED)))

#******************************************************************************#
#                              SERVEUR                                           #
#******************************************************************************#

PATH_OBJ_SERVEUR = $(PATH_OBJ)$(PATH_SERVEUR)
PATH_SRC_SERVEUR = $(PATH_SRC)$(PATH_SERVEUR)

FILES_SERVEUR = 

OBJ_SERVEUR = $(addprefix $(PATH_OBJ_SERVEUR), $(addsuffix .o , $(FILES_SERVEUR)))
SRC_SERVEUR = $(addprefix $(PATH_SRC_SERVEUR), $(addsuffix .c , $(FILES_SERVEUR)))

#******************************************************************************#
#                              FT_CLIENT                                        #
#******************************************************************************#

PATH_OBJ_CLIENT = $(PATH_OBJ)$(PATH_CLIENT)
PATH_SRC_CLIENT = $(PATH_SRC)$(PATH_CLIENT)

FILES_CLIENT = 

OBJ_CLIENT = $(addprefix $(PATH_OBJ_CLIENT), $(addsuffix .o , $(FILES_CLIENT)))
SRC_CLIENT = $(addprefix $(PATH_SRC_CLIENT), $(addsuffix .c , $(FILES_CLIENT)))

#******************************************************************************#
#                              LIBFT                                           #
#******************************************************************************#

PATH_LIB = ./libft/
PATH_INC_LIB = ./libft/
NAME_LIB = ft
HEADER_LIB = $(PATH_INC_LIB)libft.h
INC_LIB = -L $(PATH_LIB) -l $(NAME_LIB)
LIB = $(PATH_LIB)libft.a


#******************************************************************************#
#                              RULES                                           #
#******************************************************************************#

all: lib $(SERVEUR) $(CLIENT)

clean:
	@printf "\n\033[1m SUPPRESSION DES OBJETS\033[0m\n"
	@rm -rf $(PATH_OBJ)
	@make clean -C $(PATH_LIB)

fclean: clean
	@printf "\n\033[1mSUPPRESSION DE $(NAME)\033[0m\n"
	@rm -rf $(CLIENT)
	@rm -rf $(SERVEUR)
	@rm -rf $(PATH_OBJ)
	@make fclean -C $(PATH_LIB)

re: fclean all

#******************************************************************************#
#                              Compilation                                     #
#******************************************************************************#

lib:
	@make -C $(PATH_LIB)

$(SERVEUR): $(PATH_OBJ) $(PATH_OBJ_SHARED) $(OBJ_SHARED)  $(PATH_OBJ_SERVEUR) $(OBJ_SERVEUR)
	@$(CC) $(CFLAGS) $(OBJ_SHARED) $(OBJ_SERVEUR) -I $(PATH_INC) $(INC_LIB) -o $(SERVEUR)
	@echo "$(SERVEUR) has been compiled"

$(CLIENT): $(PATH_OBJ)  $(PATH_OBJ_SHARED) $(OBJ_SHARED) $(PATH_OBJ_CLIENT)  $(OBJ_CLIENT)
	@$(CC) $(CFLAGS) $(OBJ_SHARED) $(OBJ_CLIENT)  -I $(PATH_INC) $(INC_LIB) -o $(CLIENT)
	@echo "$(CLIENT) has been compiled"

$(PATH_OBJ_SHARED)%.o: $(PATH_SRC_SHARED)%.c $(HEADER) $(LIB)
	@$(CC) $(CFLAGS) -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ_CLIENT)%.o: $(PATH_SRC_CLIENT)%.c $(HEADER) $(LIB)
	@$(CC) $(CFLAGS) -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ_SERVEUR)%.o: $(PATH_SRC_SERVEUR)%.c $(HEADER) $(LIB)
	@$(CC) $(CFLAGS) -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ):
	@mkdir -p $(PATH_OBJ)

$(PATH_OBJ_SHARED):
	@mkdir -p $(PATH_OBJ_SHARED)

$(PATH_OBJ_CLIENT):
	@mkdir -p $(PATH_OBJ_CLIENT)

$(PATH_OBJ_SERVEUR):
	@mkdir -p $(PATH_OBJ_SERVEUR)