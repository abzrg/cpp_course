CXX = clang++

# Use A later Standard for the use of:
# - std::enable_if_t (c++14)
# - std::is_arithmetic_v (c++17)
CXX_FLAGS = -std=c++11 -pedantic -Wall -Wextra -ggdb -O0

matrix: matrix.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

.PHONY: clean
clean:
	$(RM) matrix

.PHONY: format
format:
	clang-format -style=file -i matrix.cpp
