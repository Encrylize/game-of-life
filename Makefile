CXX := clang++
CFLAGS := -lSDL2 --std=c++17 -g
HDRS := GridViewer.h LLCellularAutomaton.h Window.h utils.h
SRCS := main.cpp GridViewer.cpp LLCellularAutomaton.cpp Window.cpp
OBJS := $(SRCS:.cpp=.o)
EXEC := main

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CXX) -o $@ $(OBJS) $(CFLAGS)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
