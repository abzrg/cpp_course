CXX = clang++
CXX_FLAGS = -std=c++11 -pedantic -Wall -Wextra -ggdb -O0

.PHONY: all
all: deriving

deriving: deriving.cpp
	$(CXX) $(CXX_FLAGS) deriving.cpp -o $@

.PHONY: clean
clean:
	$(RM) deriving

.PHONY: format
format:
	clang-format -style=file -i *.cpp
