CXX = clang++
CXX_FLAGS = -std=c++11 -Wall -Wextra -pedantic -ggdb
SANITIZE_FLAGS = -fno-omit-frame-pointer -fsanitize=undefined,address

.PHONY: all
all: list

list: list.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

.PHONY:clean
clean:
	$(RM) -rf list

.PHONY: format
format:
	clang-format -style=file -i *.cpp *.h
