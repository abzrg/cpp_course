CXX = clang++
CXX_FLAGS = -std=c++11 -pedantic -Wall -Wextra -ggdb -O0

.PHONY: all
all: container

container: container.o main.o
	$(CXX) $(CXX_FLAGS) $^ -o $@

container.o: container.cpp container.h
	$(CXX) $(CXX_FLAGS) -c $<

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c $<

.PHONY: clean
clean:
	$(RM) container *.o

.PHONY: format
format:
	clang-format -style=file -i *.cpp
