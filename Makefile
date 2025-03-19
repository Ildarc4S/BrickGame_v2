# Настройки компилятора C
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
AR = ar
ARFLAGS = rcs

# Пути
TETRIS_SRC_DIR = brick_game/tetris
TETRIS_OBJ_DIR = build/obj/tetris
LIB_DIR = build/lib

# Исходники и объекты тетриса
TETRIS_SRCS = $(wildcard $(TETRIS_SRC_DIR)/*.c)
TETRIS_OBJS = $(patsubst $(TETRIS_SRC_DIR)/%.c, $(TETRIS_OBJ_DIR)/%.o, $(TETRIS_SRCS))

# Цели
all: $(LIB_DIR)/s21_tetris.a

$(LIB_DIR)/s21_tetris.a: $(TETRIS_OBJS) | $(LIB_DIR)
	$(AR) $(ARFLAGS) $@ $^

$(TETRIS_OBJ_DIR)/%.o: $(TETRIS_SRC_DIR)/%.c | $(TETRIS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TETRIS_OBJ_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@

clean:
	rm -rf build/obj
	rm -rf build/lib

.PHONY: all clean
