C_COMPILER = gcc
TARGET = comission_tests
UNITY_DIR = ../../../Unity
SRC_DIR = src
TEST_DIR = test

CFLAGS = -std=c99 -Wall -Wextra -Werror -fsanitize=address -g
INC_DIRS = -I$(SRC_DIR) -I$(UNITY_DIR)/src

SRC_FILES = \
    $(UNITY_DIR)/src/unity.c \
    $(SRC_DIR)/comissao.c \
    $(TEST_DIR)/test_comissao.c

all: clean compile run

compile: $(SRC_FILES)
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SRC_FILES) -o $(TARGET)

test-report:
	@mkdir -p test-results
	./comission_tests > test-results/test-output.txt 2>&1 || true

valgrind-report:
	@mkdir -p test-results
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=test-results/valgrind.txt ./comission_tests || true

coverage-report:
	@mkdir -p test-results
	gcov src/comissao.c > test-results/coverage.txt

run:
	- ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean compile run