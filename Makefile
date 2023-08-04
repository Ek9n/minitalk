# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hstein <hstein@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/02 02:12:26 by hstein            #+#    #+#              #
#    Updated: 2023/08/05 00:19:11 by hstein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		= server
CLIENT		= client
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LIBFT		= ./libft/libft.a
PRINTF		= ./printf/libftprintf.a

SERVER_SRCS = ./src/server.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_SRCS = ./src/client.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
SERVER_BONUS = server_bonus
CLIENT_BONUS = client_bonus
SERVER_BONUS_SRCS = ./src/server_bonus.c
SERVER_BONUS_OBJS = $(SERVER_BONUS_SRCS:.c=.o)
CLIENT_BONUS_SRCS = ./src/client_bonus.c
CLIENT_BONUS_OBJS = $(CLIENT_BONUS_SRCS:.c=.o)

RM			= rm -rf

all: $(SERVER) $(CLIENT)

$(LIBFT):
	$(MAKE) -C ./libft
$(PRINTF):
	$(MAKE) -C ./printf
$(SERVER): $(SERVER_OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(LIBFT) $(PRINTF) -o $(SERVER)
$(CLIENT): $(CLIENT_OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(LIBFT) $(PRINTF) -o $(CLIENT)
	
$(SERVER_BONUS): $(SERVER_BONUS_OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(SERVER_BONUS_OBJS) $(LIBFT) $(PRINTF) -o server_bonus
$(CLIENT_BONUS): $(CLIENT_BONUS_OBJS) $(LIBFT) $(PRINTF)
	$(CC) $(CFLAGS) $(CLIENT_BONUS_OBJS) $(LIBFT) $(PRINTF) -o client_bonus

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)
	# $(RM) $(SERVER_BONUS_OBJS) $(CLIENT_BONUS_OBJS) 
fclean: clean
	$(MAKE) fclean -C ./libft
	$(MAKE) fclean -C ./printf
	$(RM) $(SERVER) $(CLIENT)
	# $(RM) $(SERVER_BONUS) $(CLIENT_BONUS)

re: fclean all

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)