.PHONY: all clean rebuild tests check coverage

OS:=

ifeq ($(shell uname), Linux)
  OS=Linux
endif

ifeq ($(shell uname), Darwin)
  OS=Darwin
endif


all: tests

tests:
	mkdir -p build
	cd ./build; cmake ..
	cd ./build; cmake --build .
	./build/bin/containers_stl

rebuild: clean all

clean:
	rm -rf ./build

check:
	clang-format -i *.h
	clang-format -i test/*.cc
