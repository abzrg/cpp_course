

CXX = clang++
CXX_FLAGS = -Wall -Wextra -std=c++11 -pedantic -ggdb


.PHONY: all
all: gol

gol: main.o gol.o
	$(CXX) $(CXX_FLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $<

.PHONY: clean
clean:
	$(RM) gol *.o

.PHONY: format
format:
	clang-format -i *.cpp -style=file
