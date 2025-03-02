CXX = g++ -std=c++17
CXXFLAGS = -Wall -Werror -Wextra -g
TEST_FLAGS = -o test -lgtest
OS = $(shell uname -s)

ifeq ($(OS), Linux)
	TEST_FLAGS += -lpthread
endif

all: test style check clean

test:
	$(CXX) $(CXXFLAGS) set_test.cc $(TEST_FLAGS)
	./test

gcov-report:
	$(CXX) --coverage $(CXXFLAGS) set_test.cc $(TEST_FLAGS) -o test
	./test
	@lcov -t "stest" -o s21_test.info --no-external -c -d . --ignore-errors inconsistent
	@genhtml -o report s21_test.info
	@open ./report/index.html

style:
	clang-format -style=Google -i *.cc *.h

check: style test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test
else
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
endif

lcov:
	@brew install lcov

brew:
	@cd
	@curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

gtest:
	@brew install googletest

clean:
	@rm -f test
	@rm -rf *.dSYM
	@rm -f *.gcda
	@rm -f *.gcno
	@rm -f s21_test.info
	@rm -rf report
	@rm -f *.o *.a

.PHONY: all test clean style check
