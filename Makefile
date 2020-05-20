.PHONY: all clean fclean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror

NAME = ft_irc
SERVEUR = serveur
CLIENT = client

PATH_OBJ = ./obj/
PATH_SRC = ./src/
PATH_INC = ./includes/
PATH_SERVEUR = serveur_files/
PATH_CLIENT = client_files/
PATH_SHARED = shared/

HEADER = $(PATH_INC)$(NAME).h
HEADER_S = $(PATH_INC)$(SERVEUR).h
HEADER_C = $(PATH_INC)$(CLIENT).h

#******************************************************************************#
#                              SHARED                                          #
#******************************************************************************#

PATH_OBJ_SHARED = $(PATH_OBJ)$(PATH_SHARED)
PATH_SRC_SHARED = $(PATH_SRC)$(PATH_SHARED)

FILES_SHARED = circ_mgt \
               clean_fd \
               index_mgt \
               parsing_cmd \
               usage \
               utils

OBJ_SHARED = $(addprefix $(PATH_OBJ_SHARED), $(addsuffix .o , $(FILES_SHARED)))
SRC_SHARED = $(addprefix $(PATH_SRC_SHARED), $(addsuffix .c , $(FILES_SHARED)))

#******************************************************************************#
#                              SERVEUR                                           #
#******************************************************************************#

PATH_OBJ_SERVEUR = $(PATH_OBJ)$(PATH_SERVEUR)
PATH_SRC_SERVEUR = $(PATH_SRC)$(PATH_SERVEUR)

FILES_SERVEUR = channel_cmd \
                channel_mgt \
                client_read \
                client_write \
                command_mgt \
                create_serveur \
                error_mgt \
                looping \
                main \
                serv_nick_pm \
                serv_responses \
                serveur_accept

OBJ_SERVEUR = $(addprefix $(PATH_OBJ_SERVEUR), $(addsuffix .o , $(FILES_SERVEUR)))
SRC_SERVEUR = $(addprefix $(PATH_SRC_SERVEUR), $(addsuffix .c , $(FILES_SERVEUR)))

#******************************************************************************#
#                              CLIENT                                        #
#******************************************************************************#

PATH_OBJ_CLIENT = $(PATH_OBJ)$(PATH_CLIENT)
PATH_SRC_CLIENT = $(PATH_SRC)$(PATH_CLIENT)

FILES_CLIENT =  client_exit \
                client_record \
                create_client \
                init_envc \
                main \
                run_client \
                save_serveur_info \
                serveur_recv \
                serveur_send \

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
	@printf "\n\033[1mSUPPRESSION DES OBJETS\033[0m\n"
	@rm -rf $(PATH_OBJ)
	@make clean -C $(PATH_LIB)

fclean: clean
	@printf "\n\033[1mSUPPRESSION DE $(CLIENT)\033[0m\n"
	@rm -rf $(CLIENT)
	@printf "\n\033[1mSUPPRESSION DE $(SERVEUR)\033[0m\n"
	@rm -rf $(SERVEUR)
	@make fclean -C $(PATH_LIB)

re: fclean all

#******************************************************************************#
#                              Compilation                                     #
#******************************************************************************#

lib:
	@make -C $(PATH_LIB)

$(SERVEUR): $(PATH_OBJ) $(PATH_OBJ_SHARED) $(OBJ_SHARED) $(PATH_OBJ_SERVEUR) $(OBJ_SERVEUR)
	@$(CC) $(CFLAGS) $(OBJ_SHARED) $(OBJ_SERVEUR) -I $(PATH_INC) $(INC_LIB) -o $(SERVEUR)
	@echo "$(SERVEUR) has been compiled"

$(CLIENT): $(PATH_OBJ)  $(PATH_OBJ_SHARED) $(OBJ_SHARED) $(PATH_OBJ_CLIENT) $(OBJ_CLIENT)
	@$(CC) $(CFLAGS) $(OBJ_SHARED) $(OBJ_CLIENT) -I $(PATH_INC) $(INC_LIB) -o $(CLIENT)
	@echo "$(CLIENT) has been compiled"

$(PATH_OBJ_SHARED)%.o: $(PATH_SRC_SHARED)%.c $(HEADER) $(LIB)
	@$(CC) $(CFLAGS) -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ_CLIENT)%.o: $(PATH_SRC_CLIENT)%.c $(HEADER) $(HEADER_C) $(LIB)
	@$(CC) $(CFLAGS) -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ_SERVEUR)%.o: $(PATH_SRC_SERVEUR)%.c $(HEADER) $(HEADER_S) $(LIB)
	@$(CC) $(CFLAGS) -I $(PATH_INC) -I $(PATH_INC_LIB) -c $< -o $@

$(PATH_OBJ):
	@mkdir -p $(PATH_OBJ)

$(PATH_OBJ_SHARED):
	@mkdir -p $(PATH_OBJ_SHARED)

$(PATH_OBJ_CLIENT):
	@mkdir -p $(PATH_OBJ_CLIENT)

$(PATH_OBJ_SERVEUR):
	@mkdir -p $(PATH_OBJ_SERVEUR)