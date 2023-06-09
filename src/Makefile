CC= g++ 
CFLAGS= -Wall -Wextra -Werror -std=c++17
LIB_NAME = s21_matrix_oop
OS := $(shell uname -s)
SRC = s21_*.cc
OBJ = $(SRC:.cc=.o)
TESTFILES= tests.cc
TESTFLAGS=-lgtest

all: $(LIB_NAME).a test


$(LIB_NAME).a: clean
		$(CC) $(CFLAGS) $(SRC) -c 
		ar rcs $(LIB_NAME).a *.o

test:
	$(CC) $(TESTFILES) $(TESTFLAGS) $(CFLAGS) $(LIB_NAME).cc  -o test 
	./test

style: clean
	mv ../materials/linters/.clang-format .
	# clang-format -style=google -i *.cc
	# clang-format -style=google -i *.h
	clang-format -style=google -n *.cc
	clang-format -style=google -n *.h
	mv .clang-format ../materials/linters/


clean:
	rm -rf test build
	rm -rf *.a *.out *.o report *.gc* $(LIB_NAME).a *.info 

rebuild:
	make clean
	make all

leak:
	valgrind --tool=memcheck --leak-check=yes  ./test