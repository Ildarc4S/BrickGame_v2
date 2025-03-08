CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses
SRC_DIR = gui/cli
OBJ_DIR = build/obj

# Разделяем исходники из SRC_DIR и main.c
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
MAIN_FILE = main.c
ALL_SRCS = $(SRC_FILES) $(MAIN_FILE)

# Правильное преобразование путей
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES)) \
       $(OBJ_DIR)/main.o

all: $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

.PHONY: all clean
