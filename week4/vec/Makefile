TARGET = vector
.DEFAULT_GOAL := $(TARGET)

CXX = clang++
# CFLAGS = -Wall -Wextra -std=c++17 -pedantic -ggdb -O1 -fsanitize=address -fno-omit-frame-pointer
CFLAGS = -Wall -Wextra -std=c++17 -pedantic -ggdb

vector: main.o vec.o
	$(CXX) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $<

.PHONY: clean
clean:
	-$(RM) -f $(TARGET)
	-$(RM) -f *.o

.PHONY: format
format:
	clang-format -style=file -i *.cpp *.h
