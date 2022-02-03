# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afrasch <afrasch@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/06 14:02:35 by elenz             #+#    #+#              #
#    Updated: 2022/01/30 10:43:24 by afrasch          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
CC = gcc

SOURCE = ft_bzero.c \
ft_add_chr_to_str.c \
ft_atoi.c\
ft_calloc.c\
ft_isalnum.c\
ft_isalpha.c\
ft_isalpha_str.c\
ft_isnonum_str.c\
ft_isascii.c\
ft_isdigit.c\
ft_isprint.c\
ft_itoa.c\
ft_memchr.c\
ft_memcmp.c\
ft_memcpy.c \
ft_memmove.c \
ft_memset.c\
ft_putchar_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_putstr_fd.c\
ft_split.c\
ft_strchr.c\
ft_strdup.c\
ft_striteri.c\
ft_strjoin.c\
ft_strlcat.c\
ft_strlcpy.c\
ft_strlen.c\
ft_strmapi.c\
ft_strcmp.c \
ft_strncmp.c\
ft_strnstr.c\
ft_strrchr.c\
ft_strtrim.c\
ft_substr.c\
ft_tolower.c\
ft_toupper.c\
ft_strrev.c\
ft_utoa.c\
ft_hex2int.c\
ft_get_next_line.c\
ft_get_next_line_utils.c\
ft_free_2d.c \
ft_free_1d.c \
ft_int_strchr.c \




SOURCEBONUS = ft_lstadd_back.c\
ft_lstadd_front.c\
ft_lstclear.c\
ft_lstdelone.c\
ft_lstiter.c\
ft_lstlast.c\
ft_lstmap.c\
ft_lstnew.c\
ft_lstsize.c\

all: $(NAME) bonus

$(NAME): $(SOURCE)
	@$(CC) $(CFLAGS) -c $(SOURCE)
	@ar -rcs $(NAME) $(SOURCE:.c=.o)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus:
	@$(CC) $(CFLAGS) -c $(SOURCEBONUS)
	@ar -rcs $(NAME) $(SOURCEBONUS:.c=.o)
