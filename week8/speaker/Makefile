CXX = clang++
CXX_FLAGS = -std=c++11 -pedantic -Wall -Wextra -ggdb -O0

.PHONY: all
all: speaker

speaker: speaker.cpp
	$(CXX) $(CXX_FLAGS) speaker.cpp -o $@

.PHONY: clean
clean:
	$(RM) speaker

.PHONY: format
format:
	clang-format -style=file -i *.cpp
