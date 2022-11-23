CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -gdwarf-4 -fstandalone-debug -O0 -Wall -Wextra -Werror

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/illini_book.cc ./src/utilities.cc
	$(CXX) $(CXX_FLAGS) $^ -o $@


.DEFAULT_GOAL := exec
.PHONY: exec clean

clean:
	rm -f bin/*
