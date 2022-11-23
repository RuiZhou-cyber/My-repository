CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++2a -gdwarf-4 -fstandalone-debug
EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address,null

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/branched-linked-list.cc ./includes/branched-linked-list.hpp ./includes/node.hpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $(EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address,null)./src/driver.cc ./src/branched-linked-list.cc -o $@

bin/tests: ./tests/tests.cc ./src/branched-linked-list.cc ./includes/branched-linked-list.hpp ./includes/node.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(EXTRA_CXX_FLAGS=-Wall -Wextra -Werror -pedantic -fsanitize=address,null)./tests/tests.cc ./src/branched-linked-list.cc -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
