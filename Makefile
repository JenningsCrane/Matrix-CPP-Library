COMP_FLAGS = -Wall -Werror -Wextra
STANDART = -std=c++17
CC = gcc $(COMP_FLAGS) $(STANDART) -pthread
GCOVFLAGS = -fprofile-arcs -ftest-coverage
DEBUG = -g

OS := $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -I /usr/local/include/gtest -L /usr/local/lib -lgtest -lgtest_main -lrt -lm -lstdc++
else
	CHECK_FLAGS = -lgtest -lgtest_main -lstdc++
endif

all: matrix_oop.a

rebuild: clean all

matrix_oop.a:
	$(CC) -c matrix_oop.cc
	ar rcs libmatrix_oop.a *.o
	rm -rf *.o

test: matrix_oop.a
	$(CC) matrix_oop_test.cc -o test libmatrix_oop.a $(CHECK_FLAGS) $(DEBUG)
	./test

gcov_report: clean matrix_oop.a
	$(CC) $(GCOVFLAGS) matrix_oop_test.cc matrix_oop.cc -o test $(CHECK_FLAGS) $(DEBUG)
	./test
	gcov  *.cc
	lcov --ignore-errors mismatch --capture --directory . --output-file test.info
	genhtml test.info --output-directory report
	open report/index.html

valgrind: test
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test

leaks: clean test
	CK_FORK=no leaks --atExit -- ./test

clang-format:
	clang-format -style=Google -n *.cc *.h

clean:
	rm -rf *.o *.gcno *.gcda *.a *.info report test *.out
	rm -rf out *.gch *.gcov *.dSYM