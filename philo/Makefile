# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 17:50:06 by anilchen          #+#    #+#              #
#    Updated: 2024/11/08 15:38:01 by anilchen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -g -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MSG_EXEC_CREATED = "Executable successfully created."
MSG_CLEAN = "Cleaning up..."
MSG_FCLEAN = "Full clean up..."

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) 
	@echo $(MSG_EXEC_CREATED)

$(OBJ_DIR):	
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -rf $(OBJ_DIR)
	@echo $(MSG_CLEAN)

fclean: clean
	rm -f $(NAME)
	@echo $(MSG_FCLEAN)

re: fclean all

.PHONY: all clean fclean re
