# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nbelouar42 <nbelouar42@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/18 16:38:39 by nbelouar42        #+#    #+#              #
#    Updated: 2024/06/03 14:34:55 by nbelouar42       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
CFLAGS =  -Wextra -Wall -Werror -fsanitize=thread

INC=philo.h
SRC=philo.c utils.c maim.c
OBJS = philo.o main.o utils.o
all:philo

%.o: %.c ${INC}
	$(CC) $(CFLAGS) -o $@ -c $<
	

philo:${OBJS} 
	${CC} $(CFLAGS) $^ -o $@

clean: 
	rm -f *.o philo *.gch

fclean: clean
	rm -f philo

re: fclean all