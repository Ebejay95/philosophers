# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/21 11:50:17 by jeberle           #+#    #+#              #
#    Updated: 2024/08/21 12:04:14 by jeberle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#--------------                       PRINT                       -------------#
#------------------------------------------------------------------------------#

BLACK := \033[90m
RED := \033[31m
GREEN := \033[32m
YELLOW := \033[33m
BLUE := \033[34m
MAGENTA := \033[35m
CYAN := \033[36m
X := \033[0m

SUCCESS := \n$(MAGENTA)\
████████████████████████████████████████████████████████████████████████████████████████████████████$(X)\n\
$(X)\n\
███████  █     █  █  █        ███████  ███████  ███████  ███████  █     █  ███████  ███████  ███████$(X)\n\
█     █  █     █  █  █        █     █  █        █     █  █     █  █     █  █        █     █  █      $(X)\n\
███████  ███████  █  █        █     █  ███████  █     █  ███████  ███████  ████     ███████  ███████$(X)\n\
█        █     █  █  █        █     █        █  █     █  █        █     █  █        █   █          █$(X)\n\
█        █     █  █  ███████  ███████  ███████  ███████  █        █     █  ███████  █    ██  ███████$(X)\n\
$(X)\n\
$(MAGENTA)████████████████████████████████████████████████████████████████████████████████████████████████████$(X)\n\

#------------------------------------------------------------------------------#
#--------------                      GENERAL                      -------------#
#------------------------------------------------------------------------------#

NAME=philo
NAME_BONUS=philo_bonus

#------------------------------------------------------------------------------#
#--------------                       FLAGS                       -------------#
#------------------------------------------------------------------------------#

CC=cc
CFLAGS=-Wall -Wextra -Werror -I/usr/local/opt/readline/include
LDFLAGS=

ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address -g
endif

DEPFLAGS=-MMD -MP

#------------------------------------------------------------------------------#
#--------------                        DIR                        -------------#
#------------------------------------------------------------------------------#

OBJ_DIR := ./obj
DEP_DIR := $(OBJ_DIR)/.deps
INC_DIRS := .
SRC_DIRS := .

vpath %.c $(SRC_DIRS)
vpath %.h $(INC_DIRS)
vpath %.d $(DEP_DIR)

#------------------------------------------------------------------------------#
#--------------                        LIBS                       -------------#
#------------------------------------------------------------------------------#

LIBFT_DIR=libft
LIBFT=libft.a
LIBFT_LIB=$(LIBFT_DIR)/$(LIBFT)
LIBFTFLAGS=-L$(LIBFT_DIR) -lft

SYSLIBFLAGS=

#------------------------------------------------------------------------------#
#--------------                        SRC                        -------------#
#------------------------------------------------------------------------------#

SRCS=	mandatory/philo.c \

BONUS_SRCS= \
# bonus/minishell_bonus.c \

#------------------------------------------------------------------------------#
#--------------                      OBJECTS                      -------------#
#------------------------------------------------------------------------------#

OBJECTS := $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
BONUS_OBJECTS := $(addprefix $(OBJ_DIR)/, $(BONUS_SRCS:%.c=%.o))

#------------------------------------------------------------------------------#
#--------------                      COMPILE                      -------------#
#------------------------------------------------------------------------------#

.PHONY: all clean fclean re libft

all: $(LIBFT_LIB) $(NAME)

bonus: $(LIBFT_LIB) $(NAME_BONUS)

-include $(OBJECTS:.o=.d)
-include $(BONUS_OBJECTS:.o=.d)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(LIBFT_LIB):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning libft submodule..."; \
		git submodule add https://github.com/Ebejay95/libft.git $(LIBFT_DIR); \
		git submodule update --init --recursive; \
	else \
		echo "Updating libft submodule..."; \
		git submodule update --init --recursive --remote; \
	fi
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	@$(CC) -o $@ $^ $(LIBFTFLAGS) $(SYSLIBFLAGS) $(LDFLAGS)
	@echo "$(SUCCESS)"

$(NAME_BONUS): $(BONUS_OBJECTS)
	@$(CC) -o $@ $^ $(LIBFTFLAGS) $(SYSLIBFLAGS) $(LDFLAGS)
	@echo "$(SUCCESS)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(RED)objects deleted$(X)"

fclean: clean
	@rm -rf $(NAME_BONUS)
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)philo deleted$(X)"

re: fclean all
