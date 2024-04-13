CC = g++
CFLAGS = -Wextra -Wall -Werror
CPPFLAGS = -std=c++17
TESTLIBS = -lgtest -lgtest_main
SOURCES = Libs/Graph/Sources/s21_graph.cc Libs/Graph/Sources/s21_graph_algorithms.cc Libs/TSP/Sources/s21_tsp.cc
OBJECTS = $(SOURCES:.cc=.o)

all: s21_graph.a s21_graph_algorithms.a test menu

s21_graph.a: $(OBJECTS)
	ar rcs $@ Libs/Graph/Sources/s21_graph.o

s21_graph_algorithms.a: $(OBJECTS)
	ar rcs $@ Libs/Graph/Sources/s21_graph_algorithms.o

test: clean
	$(CC) $(CPPFLAGS) -c --coverage $(SOURCES)   
	$(CC) $(CPPFLAGS) -c Tests/*.cc
	$(CC) $(CPPFLAGS) *.o -lgtest -lgcov
	./a.out

gcov_report: clean test
	lcov -o report.info -c -d . --no-external
	genhtml -o report report.info
	open -a "Google Chrome" report/index.html
	
menu: clean
	$(CC) $(CFLAGS) $(CPPFLAGS) ContextMenu/SimpleNavigator.cc $(SOURCES) ContextMenu/main.cc -o $@
	./$@

leaks: test
	leaks -atExit -- ./a.out

clean:
	rm -rf main menu test *.dSYM *.o *.a *.gcda *.gcno *.info *.out *.txt report .clang_format report.html gcov_report
	rm -f s21_graph.a s21_graph_algorithms.a

.PHONY: all clean test style leaks gcov_report
