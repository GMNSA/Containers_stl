CC=gcc
CXXFLAGS:=-g -std=c++17 -lstdc++ -Wall -Wextra -Werror -fsanitize=address
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

HEADERS_DIR:= ./includes ./tests/includes

all: test

test: rebuild
	cd ./tests && rm -rf BUILD && cmake -B ./BUILD && make -C ./BUILD
	./test_containers.out  --gtest_filter=TestList.Erase
	rm -rf ./tests/BUILD


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
	rm -f ./objects/*
	rm -f ./test_containers.out
	rm -rf ./lib
	rm -rf ./tests/BUILD
	rm -rf ./tests/Makefile
	rm -rf ./out
	rm -rf ./gcov_obj/*

clang_check:
	done
	echo "~~~ $@ DONE ~~~";

clang_fix:

.PHONY: all clean rebuild  clang_check clang_fix
