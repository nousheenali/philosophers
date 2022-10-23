# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nali <nali@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/29 12:13:40 by nali              #+#    #+#              #
#    Updated: 2022/05/05 14:08:14 by nali             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo/philo

NAME_B	= philo_bonus/philo_bonus

LIBNAME	= philo/philo.a

LIBNAME_B	= philo_bonus/philo.a

SRCS	= philo/main.c philo/ft_atoi.c philo/ft_initialize.c\
		philo/ft_create_threads.c philo/ft_philo_utils.c

SRCS_B	= philo_bonus/main_b.c philo_bonus/ft_atoi.c philo_bonus/ft_initialize_b.c\
		philo_bonus/ft_create_prcoesses_b.c philo_bonus/ft_philo_utils_b.c
		
OBJS	= ${SRCS:.c=.o}

OBJS_B	= ${SRCS_B:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

all:	${NAME}

.c.o:	${CC} ${CFLAGS} -I -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rcs ${LIBNAME} ${OBJS}
			ranlib ${LIBNAME}
			$(CC) ${CFLAGS}  -pthread -ggdb philo/main.c -L. ${LIBNAME} -o ${NAME}
			
bonus:		${OBJS_B}
			ar rcs ${LIBNAME_B} ${OBJS_B}
			ranlib ${LIBNAME_B}
			$(CC) ${CFLAGS}  -pthread -ggdb philo_bonus/main_b.c -L. ${LIBNAME_B} -o ${NAME_B}


clean:		
			${RM} ${OBJS} ${OBJS_B}

fclean:		clean
			${RM} ${LIBNAME} ${LIBNAME_B}
			${RM} ${NAME} ${NAME_B}

re:			fclean all

.PHONY:		all clean fclean re .c.o