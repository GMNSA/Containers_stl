CC=gcc
CXXFLAGS:=-g -std=c++17 -Wall -Wextra -Werror
GCOVFLAGS:=-ftest-coverage -fprofile-arcs
OS:=

ifeq ($(shell uname), Linux)
	LDFLAGS:=-lgcov -lpthread -lsubunit -lrt -lm
	OS=Linux
endif

ifeq ($(shell uname), Darwin)
	# LDFLAGS:=-lgcov -lpthread -fprofile-args -lm
	OS=Darwin
endif

HEADERS_DIR:= ./includes

all: s21_containers.a s21_containers_gcov.a move_lib

s21_containers_gcov.a: list_gcov.o
	@echo "create static lib gcov"
	ar -src $@ ./gcov_obj/list_gcov.o

s21_containers.a: list.o
	@echo "create static lib"
	ar -src $@ ./objects/list.o

test: rebuild
	cd ./tests && rm -rf BUILD && cmake -B ./BUILD && make -C ./BUILD
	./test_containers.out # --gtest_filter=TestMatrixOOP.ForSingle

list.o:
	$(CC) -g $(CXXFLAGS) -I ${HEADERS_DIR} -c srcs/list.cpp -o objects/list.o

list_gcov.o:
	$(CC) -g $(CXXFLAGS) $(GCOVFLAGS) $(LDFLAGS) -I ${HEADERS_DIR} -c srcs/list.cpp -o gcov_obj/list_gcov.o

move_lib:
	cp ./includes/list.hpp ./
	mkdir -p lib && cp s21_containers.a ./lib && cp ./includes/list.hpp ./lib && mv s21_containers_gcov.a ./lib

rebuild: clean all

gcov_report: test
	lcov -c -d  gcov_obj/. -o gcov_obj/coverage.info
	genhtml gcov_obj/coverage.info --output-directory out
ifeq ($(OS), Linux)
	firefox ./out/index.html
else
	open ./out/index.html
endif



clean:
	rm -f ./s21_containers.a
	rm -f ./list.hpp
	rm -f ./testMatrixOOP
	rm -rf ./lib
	rm -rf ./tests/BUILD
	rm -rf ./tests/Makefile
	rm -rf ./out
	rm -rf ./gcov_obj/*

clang_check:
	done
	echo "~~~ $@ DONE ~~~";

clang_fix:

.PHONY: all clean rebuild check s21_containers.a s21_containers_gcov.a clang_check clang_fix
