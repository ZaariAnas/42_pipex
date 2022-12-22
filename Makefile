# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azari <azari@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 09:09:27 by azari             #+#    #+#              #
#    Updated: 2022/12/21 20:16:37 by azari            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libpipex.a
CC		=	cc
FLAGS	=	-Wall -Wextra -Werror 
SRCS	=	helper_func.c helper_func2.c ft_split.c  
PROG	=	pipex.c
OBJS	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(PROG) pipex.h
	@$(CC) $(FLAGS) -c $(SRCS) -I pipex.h
	@ar -rcs $(NAME) $(OBJS)
	@$(CC) $(FLAGS) $(PROG) -L. -lpipex -o pipex

norm:
	@norminette $(PROG) $(SRCS) pipex.h

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re