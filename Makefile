CFLAGS = -Wall -Werror -Wextra

all: s21_matrix_oop.a

build: s21_matrix_oop.cpp
	gcc -c $(CFLAGS) -std=c++17 s21_matrix_oop.cpp -o s21_matrix_oop.o

s21_matrix_oop.a: build
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a

clean:
	rm -rf *.o *.out s21_matrix_oop.a tests
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report *.info

rebuild:
	make clean
	make build

leaks: test
	leaks -atExit -- ./tests

clang:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cpp *.h
	rm .clang-format

test: s21_matrix_oop.a
	gcc -lgtest -lstdc++ -std=c++17 s21_matrix_oop.a s21_matrix_tests.cpp -o tests
	./tests

gcov_report: clean
	gcc -lgtest -lstdc++ -std=c++17 --coverage s21_matrix_tests.cpp s21_matrix_oop.cpp -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html