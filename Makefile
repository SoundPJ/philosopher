# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 18:49:46 by pjerddee          #+#    #+#              #
#    Updated: 2022/12/19 20:12:59 by pjerddee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

BNAME = philo_bonus

SRCS =	srcs/main.c

# BNS =	src/checker.c	\

INCS =	incs/philo.h

CFLAGS = -Wall -Werror -Wextra

INC_DIR =	incs/

SRCS_DIR = srcs/

BUILD_DIR = build

BBUILD_DIR = bbuild/

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)

BOBJS = $(BNS:%.c=$(BBUILD_DIR)/%.o)

all: $(NAME)

bonus:	$(BNAME)

$(NAME):$(OBJS)
	@gcc $(CFLAGS) -I$(INC_DIR) $(OBJS) -o $@

$(OBJS): $(BUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BNAME):$(BOBJS)
	@gcc $(CFLAGS) -I$(INC_DIR) $(BOBJS) -o $@

$(BOBJS): $(BBUILD_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -I$(INC_DIR) -c $< -o $@

cclean:
	-@rm -rf $(BUILD_DIR)
	-@rm -rf $(BBUILD_DIR)
	-@rm -f $(NAME)
	-@rm -f $(BNAME)

restart: cclean $(OBJS) $(BOBJS)
	@gcc $(CFLAGS) -I$(INC_DIR) $(OBJS) -o $(NAME)
	@gcc $(CFLAGS) -I$(INC_DIR) $(BOBJS) -o $(BNAME)

clean:
	-@rm -rf $(BUILD_DIR)
	-@rm -rf $(BBUILD_DIR)

fclean: clean
	-@rm -f $(NAME)
	-@rm -f $(BNAME)

re: fclean all

norm:
	norminette -R CheckDefine $(INCS)
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(BNS)

.PHONY: all bonus cclean restart clean fclean re norm