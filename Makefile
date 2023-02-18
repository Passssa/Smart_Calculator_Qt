.PHONY: all install uninstall clean dist test gcov_report leaks

CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
GCOV=-fprofile-arcs -ftest-coverage
OS=$(shell uname)
FOLDER=../build/
INNER_FOLDER=$(FOLDER)s21_calculator/
SOURCES_FUN:=$(shell find . -not -name "s21_test.c" -name "*.c")
SOURCES_ALL:=$(wildcard *.c)
GCOV_FLAGS=-fprofile-arcs -ftest-coverage -lgcov
CHECK_FLAGS=-lcheck -lm -lpthread
ALL_FLAGS=$(CFLAGS) $(GCOV_FLAGS) $(CHECK_FLAGS)
SRCS = s21_smart_calc.c
OBJS = $(SRCS:.c=.o)
OBJST = $(OBJS) s21_test.c
NAME = test
REPORT_NAME = report


ifeq ($(OS), Linux)
  LIBS=-lcheck -lpthread -lrt -lm -lsubunit
  OPEN_CM=xdg-open
else
  LIBS=-lcheck
  OPEN_CM=open
endif



all: install

build: clean
	mkdir $(FOLDER)
	mkdir $(INNER_FOLDER)
	cp *.c *.h  $(FOLDER)
	cd s21_calculator; cp *.h *.cpp *.ui *.pro *.icns ../$(FOLDER)s21_calculator
	cd $(INNER_FOLDER); qmake s21_calculator.pro
	make -C $(INNER_FOLDER)
	cd $(FOLDER); rm -rf *.c *.h 
	cd $(INNER_FOLDER); rm -rf *.c *.h *.cpp *.ui *.o *.ts *.pro *.qrc Makefile

install: build
	cp -rf $(INNER_FOLDER)s21_calculator.app $(HOME)/Desktop/
	make clean

uninstall: 
	rm -rf $(HOME)/Desktop/s21_calculator.app

dist:
	rm -rf my_smart_calc
	mkdir my_smart_calc
	mkdir my_smart_calc/s21_calculator
	mkdir my_smart_calc/html
	cp Makefile *.c *.h my_smart_calc/
	cd html; cp *.html *.png ../my_smart_calc/html
	cd ./s21_calculator; cp *.cpp *.h *.pro *.ui *.icns ../my_smart_calc/s21_calculator
	tar -cvzf $(HOME)/Desktop/my_smart_calc.tgz my_smart_calc/

test:
	$(CC) $(CFLAGS) -c s21_smart_calc.c -o s21_smart_calc.o
	ar rcs s21_smart_calc.a s21_smart_calc.o
	ranlib s21_smart_calc.a
	$(CC) $(CFLAGS) s21_test.c s21_smart_calc.a $(LIBS) -o s21_calculator.out
	./s21_calculator.out

cppcheck:
	cppcheck --suppress=missingIncludeSystem *.c *.h

gcov_report:
	$(CC) -o $(NAME) $(SRCS) s21_test.c $(GCOV_FLAGS) $(CHECK_FLAGS)
	./$(NAME)
	lcov -t "gcov_report" -o test.info -c -d .
	genhtml -o $(REPORT_NAME) test.info
	open report/index.html
	rm $(NAME)
	rm -rf *.gcno
	rm -rf *.gcda

dvi:
	cd doxygen && ./doxygen Doxyfile && open html/index.html

leaks: test
	CK_FORK=no leaks --atExit -- ./s21_calculator.out

style: cp linter/.clang-format ./

clean: 
	rm -f *.o *.a *.gcno *.gcda *.info *.out 
	rm -rf ./report
	rm -rf ../build
	rm -rf $(HOME)/Desktop/my_smart_calc.tar.gz
	rm -rf my_smart_calc
