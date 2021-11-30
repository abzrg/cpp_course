CXX = clang++
CXX_FLAGS = -std=c++17 -Wall -Werror -pedantic -ggdb

.PHONY: all
all: safeint

safeint: sint.o main.o
	$(CXX) $(CXX_FLAGS) $^ -o $@

sint.o: sint.cpp sint.h
	$(CXX) $(CXX_FLAGS) -c $<

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c $^

.PHONY: clean
clean:
	$(RM) -fr *.o safeint

.PHONY: format
format:
	clang-format -style=file -i *.cpp *.h
