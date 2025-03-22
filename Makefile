CC = gcc
FLAGS = -Wall -Wextra -Werror -std=c11
NCURSES_FLAGS = -lncurses
GCOV_FLAGS = --coverage
CHECK_FLAGS = -lcheck -lm -lsubunit

SRC_DIR = brick_game/tetris
TEST_DIR = tests/tetris_tests
GUI_DIR = gui/cli
BUILD_DIR = build/tetris
OBJ_DIR = $(BUILD_DIR)/obj
COV_DIR = $(BUILD_DIR)/coverage
LIB_DIR = lib

CFILES = $(wildcard $(SRC_DIR)/*.c)
TEST_FILES = $(wildcard $(TEST_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/tetris/%.o,$(CFILES))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c,$(OBJ_DIR)/tests/%.o,$(TEST_FILES))
BIN_DIR = bin

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
LIBDIR = $(PREFIX)/lib
DOCDIR = $(PREFIX)/share/doc/s21_tetris

LIB_PATH = $(LIB_DIR)/s21_tetris.a
LIB_NAME= s21_tetris.a
EXEC_NAME = s21_tetris
TEST_EXEC = test_exec

DOCGEN = doxygen
DOXYFILE = Doxyfile

.PHONY: all install uninstall clean dvi dist test gcov_report rebuild

all: $(LIB_NAME) $(EXEC_NAME)

$(LIB_NAME): $(OBJS)
	mkdir -p $(LIB_DIR)
	ar rcs $@ $^
	ranlib $@

$(OBJ_DIR)/tetris/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)/tetris
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.c
	mkdir -p $(OBJ_DIR)/tests
	$(CC) $(FLAGS) -c $< -o $@

$(EXEC_NAME): $(GUI_DIR)/*.c main.c $(LIB_NAME)
	mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $^ -o $(BIN_DIR)/$@ $(NCURSES_FLAGS)

test: $(TEST_EXEC)
	./$(BIN_DIR)/$<

$(TEST_EXEC): $(TEST_OBJS) $(LIB_PATH)
	mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $^ -o $(BIN_DIR)/$@ $(CHECK_FLAGS)

gcov_report: $(TEST_FILES) $(CFILES)
	mkdir -p $(BIN_DIR) $(COV_DIR)
	$(CC) $(FLAGS) $^ $(CHECK_FLAGS) $(GCOV_FLAGS) -o $(BIN_DIR)/gcov_exec
	./$(BIN_DIR)/gcov_exec
	lcov --capture --directory . --output-file $(COV_DIR)/coverage.info
	genhtml $(COV_DIR)/coverage.info --output-directory $(COV_DIR)

install: $(EXEC_NAME)
	mkdir -p $(BINDIR) $(LIBDIR) $(DOCDIR)
	install -m 0755 $(BIN_DIR)/$(EXEC_NAME) $(BINDIR)
	install -m 0644 $(LIB_PATH) $(LIBDIR)

uninstall:
	rm -f $(BINDIR)/$(EXEC_NAME)
	rm -f $(LIBDIR)/s21_tetris.a
	rm -rf $(DOCDIR)

dvi:
	$(DOCGEN) $(DOXYFILE)

dist: clean
	mkdir -p package
	cp -r $(SRC_DIR) $(TEST_DIR) $(GUI_DIR) Makefile tetris_readme.md package
	tar -czvf s21_tetris.tar.gz package
	rm -rf package

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR) $(LIB_DIR) *.gc* *.info

rebuild: clean all
