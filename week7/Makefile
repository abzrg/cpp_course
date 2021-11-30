CXX = clang++

# Use A later Standard for enable_if_t (C++14) and is_arithmetic_v (C++17)
CXX_FLAGS = -std=c++11 -pedantic -Wall -Wextra -ggdb -O0

matrix: matrix.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

.PHONY: format
format:
	clang-format -style=file -i matrix.cpp
