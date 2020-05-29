CXX := clang++
CFLAGS := --std=c++17 -g -Wall
LIB := -lSDL2

SRCDIR := src
BUILDDIR := build
SRCEXT := cpp
HDREXT := h

SRCS := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
HDRS := $(shell find $(SRCDIR) -type f -name *.$(HDREXT))
OBJS := $(SRCS:$(SRCDIR)/%.$(SRCEXT)=$(BUILDDIR)/%.o)
EXEC := $(BUILDDIR)/main

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(HDRS)
	@mkdir -p $(BUILDDIR)
	$(CXX) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJS) Makefile
	$(CXX) -o $@ $(OBJS) $(CFLAGS) $(LIB)

clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: clean
