# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sbos <sbos@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2022/08/31 17:51:35 by sbos          #+#    #+#                  #
#    Updated: 2022/09/01 16:11:12 by sbos          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

################################################################################

NAME := pipex

CC := cc

OBJ_DIR := obj

CFLAGS := -Wall -Wextra -Werror -Wconversion -Wpedantic -Wfatal-errors

################################################################################

LIBFT_PATH := ./submodules/libft
LIBFT_LIB_PATH := $(LIBFT_PATH)/libft.a
LIBFT := -L$(LIBFT_PATH) -lft

LIBS := $(LIBFT)

################################################################################

SOURCES :=\
src/exit.c\
src/main.c\
src/run_cmd_utils.c\
src/run_cmd.c

################################################################################

HEADERS +=\
src/pipex.h

################################################################################

ifdef O3
CFLAGS += -Ofast
endif

ifdef DEBUG
CFLAGS += -g3
endif

ifdef SAN
CFLAGS += -fsanitize=address
endif

################################################################################

FCLEANED_FILES := $(NAME)

OBJECT_PATHS := $(addprefix $(OBJ_DIR)/,$(SOURCES:.c=.o))

################################################################################

# Only cleans when MAKE_DATA changes.
DATA_FILE := .make_data
MAKE_DATA := $(shell uname) $(CFLAGS) $(LIBS) $(SOURCES)
ifneq ($(shell echo "$(MAKE_DATA)"), $(shell cat "$(DATA_FILE)" 2> /dev/null))
PRE_RULES := clean
endif

################################################################################

INCLUDES := $(sort $(addprefix -I, $(LIBFT_PATH) src))

################################################################################

.PHONY: all
all: $(PRE_RULES) $(NAME)

################################################################################

$(NAME): $(LIBFT_LIB_PATH) $(OBJECT_PATHS)
	$(CC) $(CFLAGS) $(OBJECT_PATHS) $(LIBS) -o $(NAME)
	@echo "$(MAKE_DATA)" > $(DATA_FILE)

################################################################################

$(LIBFT_LIB_PATH):
	git submodule update --init --recursive --rebase --quiet
	$(MAKE) -C $(LIBFT_PATH)

################################################################################

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

################################################################################

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/

.PHONY: fclean
fclean: clean
	git submodule update --init --recursive --rebase --quiet
	rm -f $(FCLEANED_FILES)
	$(MAKE) -C $(LIBFT_PATH) fclean

.PHONY: re
re: fclean all

################################################################################
