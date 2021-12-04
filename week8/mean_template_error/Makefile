CXX = clang++
CXX_FLAGS = -std=c++11 -pedantic -Wall -Wextra -ggdb -O0

.PHONY: all
all: mean_template_error

mean_template_error: mean_template_error.o main.o
	$(CXX) $(CXX_FLAGS) $^ -o $@

mean_template_error.o: mean_template_error.cpp mean_template_error.h
	$(CXX) $(CXX_FLAGS) -c $<

main.o: main.cpp
	$(CXX) $(CXX_FLAGS) -c $<

.PHONY: clean
clean:
	$(RM) mean_template_error *.o

.PHONY: format
format:
	clang-format -style=file -i *.cpp
