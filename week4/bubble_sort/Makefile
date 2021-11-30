CXX = clang++
CXX_FLAGS = -std=c++17 -pedantic -Wall -Wextra -ggdb

.PHONY: all
all: sort

sort: bubble_sort.o main.o
	$(CXX) $(CXX_FLAGS) $^ -o $@

bubble_sort.o: bubble_sort.cpp bubble_sort.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -f sort *.o

.PHONY: format
format:
	clang-format -style=file -i *.cpp *.h
