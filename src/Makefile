CXX=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
LCOV_FLAGS=-fprofile-arcs -ftest-coverage

# Пути к Google Test
GTEST_INCLUDE = /opt/homebrew/include
GTEST_LIB = /opt/homebrew/lib

TARGET=s21_containers
TESTS_DIR := ./tests
TEST_SRCC := $(shell find $(TESTS_DIR) -name '*.cc')
TEST_OBJS = $(TEST_SRCC:%.cc=%.o)
TEST_EXEC = $(TESTS_DIR)/test

SRC_DIR := ./
SRCC := $(shell find $(SRC_DIR) -name '*.cc' ! -name 'main.cc')
SRCH := $(shell find $(SRC_DIR) -name '*.h' -o -name '*.tpp')

OBJS = $(SRCC:%.cc=%.o)

all: $(TARGET).a
	@mkdir spare_files
	@mv *.o *.a *.info spare_files
	-rm -rf ./spare_files/*.o


$(TARGET).a: $(OBJS)
	@echo "OBJS = $(OBJS)"
	@ar rc $@ $(OBJS)
	@ranlib $@

%.o: %.cc $(SRCH)
	$(CXX) $(CFLAGS) $(LCOV_FLAGS) -I$(GTEST_INCLUDE) -c -o $@ $<


main: clean main.cc
	$(CXX) $(CFLAGS) -o $@ main.cc
	./main

test: clean $(TEST_OBJS)
	$(CXX) $(CFLAGS) $(LCOV_FLAGS) -I$(GTEST_INCLUDE) -o $(TEST_EXEC) $(TEST_OBJS) -L $(GTEST_LIB) -lgtest -lgtest_main -pthread
	./$(TEST_EXEC)
	@mkdir spare_files
	@mv ./*/*.o ./*/*.gcda ./*/*.gcno spare_files
	-rm -rf ./spare_files

gcov_report: test
	lcov -t "gcov_report" -d $(TESTS_DIR) --ignore-errors mismatch -o report.info --no-external -c
	genhtml -o report report.info
	open ./report/index.html

valgrind: test
	valgrind --vgdb=no --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes --verbose --read-var-info=yes ./$(TEST_EXEC)

leaks: test
	CK_FORK=no leaks --atExit -- ./$(TEST_EXEC)

style_check:
	find . -name "*.cc" -o -name "*.h" -o -name "*.tpp" | xargs clang-format -style=Google -n

style_set:
	find . -name "*.cc" -o -name "*.h" -o -name "*.tpp" | xargs clang-format -style=Google -i

clean:
	rm -rf $(OBJS) $(TEST_OBJS)
	rm -rf *.a
	rm -rf *.o
	rm -rf $(TEST_EXEC) main
	rm -rf tests/*.gcda
	rm -rf tests/*.gcno
	rm -rf *.info
	rm -rf report/
	rm -rf spare_files/
	clear
